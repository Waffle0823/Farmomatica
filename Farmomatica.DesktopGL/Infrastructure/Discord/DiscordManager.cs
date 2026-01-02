using System;
using System.IO;
using System.Text.Json;
using DiscordSharp;
using Farmomatica.Core.Common.Logging;
using Farmomatica.DesktopGL.Settings;

namespace Farmomatica.DesktopGL.Infrastructure.Discord;

internal sealed record DiscordTokenCache(
    string AccessToken,
    string RefreshToken,
    DateTime ExpiresAt
);

public static class DiscordManager
{
    private static readonly Client _client = new();
    private static string _codeVerifier;
    
    private static bool _initialized;

    private static void SaveToken(string accessToken, string refreshToken, int expiresInSeconds)
    {
        DiscordTokenCache cache = new(
            accessToken,
            refreshToken,
            DateTime.UtcNow.AddSeconds(expiresInSeconds)
        );

        string json = JsonSerializer.Serialize(cache);
        File.WriteAllText(SystemPaths.DiscordTokenCachePath, json);
    }

    private static bool TryLoadToken(out DiscordTokenCache cache)
    {
        cache = null!;

        if (!File.Exists(SystemPaths.DiscordTokenCachePath))
            return false;

        try
        {
            string json = File.ReadAllText(SystemPaths.DiscordTokenCachePath);
            cache = JsonSerializer.Deserialize<DiscordTokenCache>(json)!;
            return true;
        }
        catch
        {
            return false;
        }
    }

    private static void OnLog(string message, LoggingSeverity severity)
    {
        switch (severity)
        {
            case LoggingSeverity.Verbose:
                Log.Debug("Discord", message);
                break;

            case LoggingSeverity.Info:
            case LoggingSeverity.None:
            default:
                Log.Info("Discord", message);
                break;

            case LoggingSeverity.Warning:
                Log.Warn("Discord", message);
                break;

            case LoggingSeverity.Error:
                Log.Error("Discord", message);
                break;
        }
    }

    private static void OnStatusChanged(Client.Status status, Client.Error error, int errorDetail)
    {
        Log.Info("Discord", "Status changed: " + status);

        if (error != Client.Error.None)
            Log.Error("Discord", "Error while status changing: " + errorDetail);

        if (status == Client.Status.Ready) ClientReady();
    }

    private static void OnAuthorizeResult(ClientResult result, string code, string redirectUri)
    {
        Log.Info("Discord", $"Authorization result: [{result.Error()}] [{code}] [{redirectUri}]");

        if (!result.Successful()) return;

        GetTokenFromCode(code, redirectUri);
    }

    private static void ProcessToken(ClientResult result, string accessToken, string refreshToken, AuthorizationTokenType tokenType, int expiresIn, string scopes)
    {
        if (!string.IsNullOrEmpty(accessToken))
        {
            Log.Info("Discord", expiresIn.ToString());

            SaveToken(accessToken, refreshToken, expiresIn);
            OnReceivedToken(accessToken);
        }
        else
        {
            Log.Error("Discord", "Error while processing token: " + result.Error());

            OnRetrieveTokenFailed();
        }
    }

    private static void GetTokenFromCode(string code, string redirectUri)
    {
        _client.GetToken(DiscordSettings.ClientId, code, _codeVerifier, redirectUri, ProcessToken);
    }

    private static void OnReceivedToken(string token)
    {
        Log.Info("Discord", "Token Received");
        _client.UpdateToken(AuthorizationTokenType.Bearer, token, (ClientResult result) => { _client.Connect(); });
    }

    private static void OnRetrieveTokenFailed()
    {
        Log.Error("Discord", "Error while getting discord token");
    }

    private static void ClientReady()
    {
        Activity activity = new();
        activity.SetType(ActivityTypes.Playing);
        _client.UpdateRichPresence(activity, (result) =>
        {
            if (result.Successful())
            {
                Log.Info("Discord", "Rich presence updated!");
            }
            else
            {
                Log.Error("Discord", "Failed to update rich presence");
            }
        });
    }

    private static void StartOAuthFlow()
    {
        AuthorizationCodeVerifier authorizationVerifier = _client.CreateAuthorizationCodeVerifier();
        _codeVerifier = authorizationVerifier.Verifier();

        AuthorizationArgs args = new();
        args.SetClientId(DiscordSettings.ClientId);
        args.SetScopes(Client.GetDefaultPresenceScopes());
        args.SetCodeChallenge(authorizationVerifier.Challenge());
        _client.Authorize(args, OnAuthorizeResult);
    }

    public static void Initialize()
    {
        if (_initialized) return;
        
        _client.AddLogCallback(OnLog, LoggingSeverity.None);
        _client.SetStatusChangedCallback(OnStatusChanged);

        Directory.CreateDirectory(SystemPaths.TokenCachePath);

        if (TryLoadToken(out DiscordTokenCache cache))
        {
            if (cache.ExpiresAt > DateTime.UtcNow)
            {
                Log.Info("Discord", "Using cached access token");
                _client.UpdateToken(
                    AuthorizationTokenType.Bearer,
                    cache.AccessToken,
                    _ => _client.Connect()
                );
                return;
            }

            Log.Info("Discord", "Refreshing token");
            _client.RefreshToken(DiscordSettings.ClientId, cache.RefreshToken, ProcessToken);
            return;
        }

        StartOAuthFlow();

        _initialized = true;
    }
}