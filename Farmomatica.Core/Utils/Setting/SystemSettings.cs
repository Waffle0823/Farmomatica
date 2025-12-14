using System;
using System.IO;

namespace Farmomatica.Core.Utils.Setting;

internal static class SystemPaths
{
    private static readonly string _appDataPath = Path.Combine(Environment.GetFolderPath(Environment.SpecialFolder.ApplicationData), ".farmomatica");

    public static readonly string LogFolderPath = Path.Combine(_appDataPath, "logs");
    public const string LogFileName = "latest.log";
}

internal static class TimeoutSettings
{
    public static readonly TimeSpan ArchiveTimeout = TimeSpan.FromSeconds(60);
}