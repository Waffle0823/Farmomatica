using System;

namespace Farmomatica.Core.Common.Logging;

/// <summary>
/// Defines the severity levels for log entries.
/// </summary>
public enum LogLevel
{
    Debug = 0,
    Info = 1,
    Warn = 2,
    Error = 3,
    Critical = 4
}

/// <summary>
/// Represents an immutable log entry produced by the game logging system.
/// </summary>
/// <param name="logLevel"></param>
/// <param name="message"></param>
/// <param name="category"></param>
public readonly struct LogEntry(LogLevel logLevel, string message, string category = "Default")
{
    public DateTime Time { get; } = DateTime.UtcNow;
    public LogLevel Level { get; } = logLevel;
    public string Category { get; } = category;
    public string Message { get; } = message;
}

/// <summary>
/// Represents an immutable crash entry produced by the game logging system.
/// </summary>
/// <param name="exception"></param>
public readonly struct CrashEntry(Exception exception)
{
    public DateTime Time { get; } = DateTime.UtcNow;
    public Exception Exception { get; } = exception;
}