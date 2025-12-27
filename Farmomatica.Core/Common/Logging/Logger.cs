using System;
using System.Threading.Channels;
using System.Threading.Tasks;

namespace Farmomatica.Core.Common.Logging;

public sealed class Logger : IDisposable
{
    private readonly ILogSink _sink;

    private readonly Channel<LogEntry> _logChannel = Channel.CreateUnbounded<LogEntry>();
    private readonly Channel<CrashEntry> _crashChannel = Channel.CreateUnbounded<CrashEntry>();

    private readonly Task _processTask;

    public Logger(ILogSink sink)
    {
        _sink = sink ?? throw new ArgumentNullException(nameof(sink));

        _processTask = Task.WhenAll(ProcessLog(), ProcessCrash());
    }

    public void Log(in LogEntry entry)
    {
        _logChannel.Writer.TryWrite(entry);
    }

    public void Crash(in CrashEntry entry)
    {
        _crashChannel.Writer.TryWrite(entry);
    }

    public void Dispose()
    {
        _logChannel.Writer.Complete();
        _crashChannel.Writer.Complete();

        _processTask.Wait();

        _sink.Dispose();
    }

    private async Task ProcessLog()
    {
        await foreach (LogEntry entry in _logChannel.Reader.ReadAllAsync())
        {
            _sink.TryWrite(entry);
        }
    }

    private async Task ProcessCrash()
    {
        await foreach (CrashEntry entry in _crashChannel.Reader.ReadAllAsync())
        {
            _sink.TryWriteCrash(entry);
        }
    }
}