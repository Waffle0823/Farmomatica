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

    public static void Debug(string message, string category) => _instance?.Log(new LogEntry(LogLevel.Debug, message, category));

    public static void Info(string message, string category) => _instance?.Log(new LogEntry(LogLevel.Info, message, category));

    public static void Warn(string message, string category) => _instance?.Log(new LogEntry(LogLevel.Warn, message, category));

    public static void Error(string message, string category) => _instance?.Log(new LogEntry(LogLevel.Error, message, category));

    public static void Critical(string message, string category) => _instance?.Log(new LogEntry(LogLevel.Critical, message, category));

    public static void Crash(Exception ex) => _instance?.Crash(new CrashEntry(ex));
}