using System;
using System.IO;

namespace Farmomatica.DesktopGL.Settings;

public static class SystemPaths
{
    private static readonly string _appDataPath = Path.Combine(Environment.GetFolderPath(Environment.SpecialFolder.ApplicationData), ".farmomatica");

    public static readonly string LogArchiveFolderPath = Path.Combine(_appDataPath, "logs");
    public static readonly string LogFilePath = Path.Combine(LogArchiveFolderPath, "latest.log");
    public static readonly string CrashFolderPath = Path.Combine(_appDataPath, "crash-reports");

    public static readonly string TokenCachePath = Path.Combine(_appDataPath, "token-caches");
    public static readonly string DiscordTokenCachePath = Path.Combine(TokenCachePath, "discord_token.json");
}

public static class DiscordSettings
{
    public const ulong ClientId = 1446220858841366719;
}