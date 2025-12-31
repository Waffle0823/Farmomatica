using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.IO.Compression;
using System.Linq;
using System.Reflection;
using System.Text;
using System.Threading;
using Farmomatica.Core.Common.Logging;
using Farmomatica.DesktopGL.Infrastructure.Steam;
using Farmomatica.DesktopGL.Platform;
using Steamworks;

namespace Farmomatica.DesktopGL.Sinks;

public sealed class LogSink(string logFilePath, string archiveFolderPath, string crashFolderPath) : ILogSink
{
    private readonly StreamWriter _logWriter = new(logFilePath, true);

    private static readonly Assembly _executingAssembly = Assembly.GetExecutingAssembly();
    private static readonly Assembly[] _loadedAssemblies = AppDomain.CurrentDomain.GetAssemblies();

    private static readonly SystemInfoProvider _systemInfo = new();

    private bool _disposing;

    public bool TryWrite(in LogEntry entry)
    {
        if (_disposing) return false;

        string message = $"[{entry.Time:yyyy-MM-dd HH:mm:ss.fff}] [{entry.Level.ToString()}] [{entry.Category}] {entry.Message}";

#if DEBUG
        string Color(LogLevel level) => level switch
        {
            LogLevel.Debug => "\u001b[36m",
            LogLevel.Info => "\u001b[32m",
            LogLevel.Warn => "\u001b[33m",
            LogLevel.Error => "\u001b[31m",
            LogLevel.Critical => "\u001b[1;31m",
            _ => "\u001b[0m"
        };

        Console.WriteLine(Color(entry.Level) + message + "\u001b[0m");
#endif

        try
        {
            _logWriter.WriteLine(message);
        }
        catch (Exception)
        {
            return false;
        }

        return true;
    }

    public bool TryWriteCrash(in CrashEntry entry)
    {
        try
        {
            StringBuilder builder = new();

            builder.AppendLine("=== FARMOMATICA CRASH REPORT ===");
            builder.AppendLine($"Time: {entry.Time:yyyy-MM-dd HH:mm:ss}");
            builder.AppendLine();
            builder.AppendLine("----- Environment Info -----");
            builder.AppendLine($"Product Name: {_executingAssembly.GetCustomAttributes<AssemblyProductAttribute>().First().Product}");
            builder.AppendLine($"Product Version: {_executingAssembly.GetName().Version}");
            builder.AppendLine($"OS: {Environment.OSVersion}");
            builder.AppendLine($"Runtime: {Environment.Version}");
            builder.AppendLine($"CPU: {_systemInfo.GetCpuName()}");
            builder.AppendLine($"RAML {_systemInfo.GetRamBytes() / 1073741824}GB");
            builder.AppendLine();
            builder.AppendLine("----- Steam Info -----");
            builder.AppendLine($"Steam Initialized: {SteamManager.Initialized}");
            builder.AppendLine($"User: {(SteamManager.Initialized ? SteamFriends.GetPersonaName() : "Unknown")}");
            builder.AppendLine($"Steam ID: {(SteamManager.Initialized ? SteamUser.GetSteamID() : "Unknown")}");
            builder.AppendLine();
            builder.AppendLine("----- Runtime Info -----");
            builder.AppendLine($"Args: {string.Join(" ", Environment.GetCommandLineArgs())}");
            builder.AppendLine($"Process Id: {Environment.ProcessId}");
            builder.AppendLine($"Working Set: {Process.GetCurrentProcess().WorkingSet64 / 1048576} MB");
            builder.AppendLine();
            builder.AppendLine("----- Thread Info -----");
            builder.AppendLine($"Thread: {Thread.CurrentThread.Name ?? "Unknown"}");
            builder.AppendLine($"Thread ID: {Environment.CurrentManagedThreadId}");
            builder.AppendLine($"Thread Pool: {Thread.CurrentThread.IsThreadPoolThread}");
            builder.AppendLine($"Priority: {Thread.CurrentThread.Priority}");
            builder.AppendLine();
            builder.AppendLine("----- Exception -----");
            builder.AppendLine($"Type: {entry.Exception.GetType()}");
            builder.AppendLine($"Message: {entry.Exception.Message}");
            builder.AppendLine($"HResult: {entry.Exception.HResult}");
            builder.AppendLine();
            builder.AppendLine("----- StackTrace -----");
            builder.AppendLine(entry.Exception.StackTrace);
            builder.AppendLine();

            Exception current = entry.Exception.InnerException;
            while (current != null)
            {
                builder.AppendLine("----- Inner Exception -----");
                builder.AppendLine($"Type: {current.GetType()}");
                builder.AppendLine($"Message: {current.Message}");
                builder.AppendLine($"HResult: {current.HResult}");
                builder.AppendLine($"StackTrace: {current.StackTrace ?? "N/A"}");
                builder.AppendLine();
                current = current.InnerException;
            }

            builder.AppendLine("----- Loaded Assemblies -----");

            foreach (Assembly asm in _loadedAssemblies)
            {
                builder.AppendLine($"{asm.GetName()} {asm.GetName().Version}");
            }

            Directory.CreateDirectory(crashFolderPath);

            string crashPath = Path.Combine(crashFolderPath, $"CrashReport_{DateTime.Now:yyyy-MM-dd_HH.mm.ss}.txt");

            File.WriteAllText(crashPath, builder.ToString());

            return true;
        }
        catch (Exception)
        {
            return false;
        }
    }

    public void Flush()
    {
        _logWriter.Flush();
    }

    public void Dispose()
    {
        _disposing = true;

        _logWriter.Dispose();

        ArchiveLogs();
    }

    private void ArchiveLogs()
    {
        if (!File.Exists(logFilePath) || new FileInfo(logFilePath).Length == 0) return;

        try
        {
            Directory.CreateDirectory(archiveFolderPath);

            string archivePath = Path.Combine(archiveFolderPath, GetArchiveName());

            using FileStream source = File.OpenRead(logFilePath);
            using FileStream destination = File.Create(archivePath);
            using GZipStream gzip = new(destination, CompressionLevel.Optimal);

            source.CopyTo(gzip);
        }
        catch (Exception ex)
        {
#if DEBUG
            Console.WriteLine("Error while archiving logs failed: " + ex.Message);
#endif
            return;
        }

        try
        {
            File.Delete(logFilePath);
        }
        catch (Exception ex)
        {
#if DEBUG
            Console.WriteLine("Error while deleting log file: " + ex.Message);
#endif
        }
    }

    private string GetArchiveName()
    {
        string todayPrefix = DateTime.Today.ToString("yyyy-MM-dd");
        string pattern = $"{todayPrefix}-*.log.gz";

        try
        {
            IEnumerable<string> existingFiles = Directory.EnumerateFiles(archiveFolderPath, pattern, SearchOption.TopDirectoryOnly);

            int nextIndex = existingFiles.Count() + 1;

            return $"{todayPrefix}-{nextIndex}.log.gz";
        }
        catch (Exception ex)
        {
#if DEBUG
            Console.WriteLine("Error while getting archive name: " + ex.Message);
#endif
            return $"{todayPrefix}-1.log.gz";
        }
    }
}