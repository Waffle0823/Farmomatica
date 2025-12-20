using System;
using System.IO;
using Farmomatica.Core.Utils.Logger;
using Farmomatica.Core.Utils.SystemInfo;

namespace Farmomatica.Android.Platform;

public sealed class SystemInfoProvider : SystemInfoCollector
{
    private string _cachedCpuName;
    private ulong? _cachedRamBytes;

    protected override string GetCpuNameInternal()
    {
        if (_cachedCpuName != null)
            return _cachedCpuName;

        try
        {
            foreach (string line in File.ReadLines("/proc/cpuinfo"))
            {
                
                if (!line.StartsWith("Hardware") && !line.StartsWith("model name") && !line.StartsWith("Processor"))
                    continue;

                _cachedCpuName = line.Split(':')[1].Trim();
                return _cachedCpuName;
            }

            return null;
        }
        catch (Exception ex)
        {
            Logger.Error("System Info Collector", "Error while getting cpu name from android: " + ex.Message);
            return null;
        }
    }

    protected override ulong? GetRamBytesInternal()
    {
        if (_cachedRamBytes != null)
            return _cachedRamBytes;

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
            Logger.Error("System Info Collector", "Error while getting ram bytes from android: " + ex.Message);
            return null;
        }
    }
}