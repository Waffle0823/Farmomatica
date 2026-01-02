using Farmomatica.Core.Common.Platform;
using Farmomatica.DesktopGL.Infrastructure.Discord;
using Farmomatica.DesktopGL.Infrastructure.Steam;

namespace Farmomatica.DesktopGL.Platform;

public sealed class PlatformRuntime : IPlatformRuntime
{
    public void Initialize()
    {
        SteamManager.Initialize();
        DiscordManager.Initialize();
    }

    public void Update()
    {
        SteamManager.RunCallbacks();
        DiscordSharp.NativeMethods.Discord_RunCallbacks();
    }

    public void Shutdown()
    {
        SteamManager.Shutdown();
    }
}