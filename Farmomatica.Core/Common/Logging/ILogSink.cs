using System;

namespace Farmomatica.Core.Common.Logging;

/// <summary>
/// Represents a target sink that receives log entries from the logging system.
/// </summary>
public interface ILogSink : IDisposable
{
    /// <summary>
    /// Writes a log entry to the sink.
    /// </summary>
    /// <param name="entry"></param>
    void Write(in LogEntry entry);

    /// <summary>
    /// Writes a crash entry to the sink.
    /// </summary>
    /// <param name="entry"></param>
    void WriteCrash(in CrashEntry entry);

    /// <summary>
    /// Flushes any buffered data to the underlying storage.
    /// </summary>
    void Flush();
}