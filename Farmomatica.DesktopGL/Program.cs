using Farmomatica.Core.Common.Logging;
using Farmomatica.DesktopGL.Platform;
using Farmomatica.DesktopGL.Settings;
using Farmomatica.DesktopGL.Sinks;

using Logger logger = new(new LogSink(SystemPaths.LogFilePath, SystemPaths.LogArchiveFolderPath, SystemPaths.CrashFolderPath));

Log.Initialize(logger);

using var game = new Farmomatica.Core.Game1(new PlatformRuntime());
game.Run();
