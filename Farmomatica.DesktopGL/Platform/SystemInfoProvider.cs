using System;
using Farmomatica.Core.Utils.Logger;
using Farmomatica.Core.Utils.SystemInfo;

#if WINDOWS
using System.Management;
#endif

#if LINUX
using System.IO;
#endif

#if OSX
using System.Diagnostics;
#endif

namespace Farmomatica.DesktopGL.Platform;

public sealed class SystemInfoProvider : SystemInfoCollector
{
    private string _cachedCpuName;
    private ulong? _cachedRamBytes;

    protected override string GetCpuNameInternal()
    {
        if (_cachedCpuName != null)
            return _cachedCpuName;

#if WINDOWS
        try
        {
            using ManagementObjectSearcher searcher = new("select Name from Win32_Processor");

            foreach (ManagementBaseObject mbo in searcher.Get())
            {
                if (mbo["Name"] is not string name)
                    continue;

                _cachedCpuName = name;
                return _cachedCpuName;
            }

            return null;
        }
        catch (Exception ex)
        {
            Logger.Error("System Info Collector", "Error while getting cpu name from windows: " + ex.Message);
            return null;
        }
#endif

#if LINUX
        try
        {
            string[] lines = File.ReadAllLines("/proc/cpuinfo");

            foreach (string line in lines)
            {
                if (!line.StartsWith("model name"))
                    continue;

                _cachedCpuName = line.Split(':')[1].Trim();
                return _cachedCpuName;
            }

            return null;
        }
        catch (Exception ex)
        {
            Logger.Error("System Info Collector", "Error while getting cpu name from linux: " + ex.Message);
            return null;
        }
#endif

#if OSX
        try
        {
            using Process process = new()
            {
                StartInfo = new ProcessStartInfo
                {
                    FileName = "sysctl",
                    Arguments = "-n machdep.cpu.brand_string",
                    RedirectStandardOutput = true,
                    UseShellExecute = false,
                    CreateNoWindow = true
                }
            };

            process.Start();
            string result = process.StandardOutput.ReadToEnd().Trim();
            process.WaitForExit();

            _cachedCpuName = string.IsNullOrWhiteSpace(result) ? null : result;
            return _cachedCpuName;
        }
        catch (Exception ex)
        {
            Logger.Error("System Info Collector", "Error while getting cpu name from macos: " + ex.Message);
            return null;
        }
#endif

        Logger.Warning("System Info Collector", "Current OS isn't supported for system info collector");
        return null;
    }

    protected override ulong? GetRamBytesInternal()
    {
        if (_cachedRamBytes != null)
            return _cachedRamBytes;

#if WINDOWS
        try
        {
            using ManagementObjectSearcher searcher = new("Select TotalPhysicalMemory From Win32_ComputerSystem");

            foreach (ManagementBaseObject mbo in searcher.Get())
            {
                if (mbo["TotalPhysicalMemory"] is not ulong totalPhysicalMemory)
                    continue;

                _cachedRamBytes = totalPhysicalMemory;
                return totalPhysicalMemory;
            }

            return null;
        }
        catch (Exception ex)
        {
            Logger.Error("System Info Collector", "Error while getting ram bytes from windows: " + ex.Message);
            return null;
        }
#endif

#if LINUX
        try
        {
            foreach (string line in File.ReadLines("/proc/meminfo"))
            {
                if (!line.StartsWith("MemTotal"))
                    continue;

                if (!ulong.TryParse(line.Split(':')[1].Trim().Split(' ')[0], out ulong memTotal))
                    return null;

                memTotal *= 1024UL;
                _cachedRamBytes = memTotal;
                return memTotal;
            }

            return null;
        }
        catch (Exception ex)
        {
            Logger.Error("System Info Collector", "Error while getting ram bytes from linux: " + ex.Message);
            return null;
        }
#endif

#if OSX
        try
        {
            using Process process = new()
            {
                StartInfo = new ProcessStartInfo
                {
                    FileName = "sysctl",
                    Arguments = "-n hw.memsize",
                    RedirectStandardOutput = true,
                    UseShellExecute = false,
                    CreateNoWindow = true
                }
            };

            process.Start();
            string result = process.StandardOutput.ReadToEnd().Trim();
            process.WaitForExit();

            if (!ulong.TryParse(result, out ulong value))
                return null;

            _cachedRamBytes = value;
            return value;
        }
        catch (Exception ex)
        {
            Logger.Error("System Info Collector", "Error while getting ram bytes from macos: " + ex.Message);
            return null;
        }
#endif

        Logger.Warning("System Info Collector", "Current OS isn't supported for system info collector");
        return null;
    }
}