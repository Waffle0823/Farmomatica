using System;

namespace Farmomatica.Core.Common.Logging;

public static class Log
{
    private static Logger _instance;

    public static void Initialize(Logger logger)
    {
        if (_instance != null) return;

        _instance = logger;
    }

    public static void Debug(string category, string message) => _instance?.Log(new LogEntry(LogLevel.Debug, message, category));

    public static void Info(string category, string message) => _instance?.Log(new LogEntry(LogLevel.Info, message, category));

    public static void Warn(string category, string message) => _instance?.Log(new LogEntry(LogLevel.Warn, message, category));

    public static void Error(string category, string message) => _instance?.Log(new LogEntry(LogLevel.Error, message, category));

    public static void Critical(string category, string message) => _instance?.Log(new LogEntry(LogLevel.Critical, message, category));

    public static void Crash(Exception ex) => _instance?.Crash(new CrashEntry(ex));
}