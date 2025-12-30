using System;
using System.Threading.Channels;
using System.Threading.Tasks;

namespace Farmomatica.Core.Common.Logging;

public sealed class Logger : IDisposable
{
    private readonly ILogSink _sink;

    private readonly Channel<LogEntry> _logChannel = Channel.CreateUnbounded<LogEntry>();

    private readonly Task _processTask;

    public Logger(ILogSink sink)
    {
        _sink = sink ?? throw new ArgumentNullException(nameof(sink));

        _processTask = Task.Run(ProcessLog);
    }

    public void Log(in LogEntry entry)
    {
        _logChannel.Writer.TryWrite(entry);
    }

    public void Crash(in CrashEntry entry)
    {
        if (!_sink.TryWriteCrash(entry))
        {
#if DEBUG
            Console.WriteLine("Error while writing crash report");
#endif
        }
    }

    public void Dispose()
    {
        _logChannel.Writer.Complete();

        _processTask.Wait();

        _sink.Dispose();
    }

    private async Task ProcessLog()
    {
        await foreach (LogEntry entry in _logChannel.Reader.ReadAllAsync())

        {
            if (!_sink.TryWrite(entry))
            {
#if DEBUG
                Console.WriteLine("Error while writing log");
#endif
            }
        }
    }
}