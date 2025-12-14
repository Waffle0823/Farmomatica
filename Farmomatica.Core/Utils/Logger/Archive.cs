using System;
using System.Collections.Generic;
using System.IO;
using System.IO.Compression;
using System.Linq;
using System.Threading;
using System.Threading.Channels;
using System.Threading.Tasks;
using Farmomatica.Core.Utils.Setting;

namespace Farmomatica.Core.Utils.Logger;

public static class Archive
{
    private static readonly Channel<string> _writeChannel = Channel.CreateUnbounded<string>();

    private static Task _writeTask;
    private static readonly CancellationTokenSource _writeCts = new();
    private static readonly SemaphoreSlim _archiveSemaphore = new(1, 1);

    static Archive()
    {
        _writeTask = ProcessWriteQueue();
    }

    public static void Write(string line)
    {
        _writeChannel.Writer.TryWrite(line);
    }

    public static Task WriteAsync(string message, CancellationToken ct = default)
    {
        return _writeChannel.Writer.WriteAsync(message, ct).AsTask();
    }

    public static void ArchiveCrash() => ArchiveLogsAsync().GetAwaiter().GetResult();

    public static async Task ArchiveCrashAsync(string content)
    {
        string archivePath = Path.Combine(SystemPaths.CrashFolderPath, $"CrashReport_{DateTime.Now:yyyy-MM-dd_HH.mm.ss}.txt");

        try
        {
            await File.WriteAllTextAsync(archivePath, content);
        }
        catch (Exception ex)
        {
            await Console.Error.WriteLineAsync("Error while archiving crash: " + ex.Message);
        }
    }

    public static void ArchiveLogs() => ArchiveLogsAsync().GetAwaiter().GetResult();

    public static async Task ArchiveLogsAsync()
    {
        await _archiveSemaphore.WaitAsync();

        try
        {
            string latestPath = Path.Combine(SystemPaths.LogFolderPath, SystemPaths.LogFileName);
            if (!File.Exists(latestPath)) return;

            await _writeCts.CancelAsync();
            await _writeTask.WaitAsync(TimeoutSettings.ArchiveTimeout);

            await using (FileStream fs = File.OpenRead(latestPath))
            await using (GZipStream gz = new(File.Create(GetArchiveName()), CompressionMode.Compress))
            {
                await fs.CopyToAsync(gz);
            }

            File.Delete(latestPath);

            _writeCts.TryReset();

            if (_writeTask is null || _writeTask.IsCompleted)
                _writeTask = ProcessWriteQueue();
        }
        catch (TimeoutException ex)
        {
            await Console.Error.WriteLineAsync("Timeout caused while waiting for log processing task: " + ex.Message);
        }
        catch (Exception ex)
        {
            await Console.Error.WriteLineAsync("Error while archiving logs: " + ex.Message);
        }
        finally
        {
            _archiveSemaphore.Release();
        }
    }

    private static async Task ProcessWriteQueue()
    {
        await using StreamWriter writer = new(Path.Combine(SystemPaths.LogFolderPath, SystemPaths.LogFileName), append: true);
        writer.AutoFlush = true;

        try
        {
            await foreach (string line in _writeChannel.Reader.ReadAllAsync(_writeCts.Token))
            {
                await writer.WriteLineAsync(line);
            }
        }
        catch (OperationCanceledException)
        {
            while (_writeChannel.Reader.TryRead(out string line))
            {
                await writer.WriteLineAsync(line);
            }
        }
        catch (Exception ex)
        {
            await Console.Error.WriteLineAsync(ex.Message);
        }
    }

    private static string GetArchiveName()
    {
        try
        {
            string prefix = DateTime.Today.ToString("yyyy-MM-dd");

            List<int> indices = Directory.GetFiles(SystemPaths.LogFolderPath, "*log.gz", SearchOption.TopDirectoryOnly)
                .Select(Path.GetFileName)
                .Where(name => name.StartsWith(prefix, StringComparison.OrdinalIgnoreCase))
                .Select(name =>
                {
                    string number = name[(prefix.Length + 1)..^7];

                    return int.TryParse(number, out int index) ? index : -1;
                })
                .Where(index => index > 0)
                .ToList();

            string archiveName = $"{prefix}-{indices.DefaultIfEmpty(0).Max() + 1}.log.gz";
            string archivePath = Path.Combine(SystemPaths.LogFolderPath, archiveName);

            return archivePath;
        }
        catch
        {
            Console.Error.WriteLine("Error while getting new archive name");
            return null;
        }
    }
}