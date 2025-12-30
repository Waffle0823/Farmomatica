using Steamworks;

namespace Farmomatica.DesktopGL.Infrastructure.Steam;

public static class SteamManager
{
    public static bool Initialized { get; private set; }

    public static bool Initialize()
    {
        if (!SteamAPI.Init())
            return false;

        Initialized = true;
        return true;
    }

    public static void Shutdown()
    {
        if (Initialized)
            SteamAPI.Shutdown();
    }

    public static void RunCallbacks()
    {
        if (Initialized)
            SteamAPI.RunCallbacks();
    }
}