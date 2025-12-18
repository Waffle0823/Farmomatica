using System;
using System.Management;
using Farmomatica.Core.Utils.Logger;
using Farmomatica.Core.Utils.SystemInfo;

namespace Farmomatica.WindowsDX.Platform;

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
            using ManagementObjectSearcher searcher = new("select Name from Win32_Processor");

            foreach (ManagementBaseObject mbo in searcher.Get())
            {
                if (mbo["Name"] is not string name)
                    continue;

                _cachedCpuName = name;
                return name;
            }

            return null;
        }
        catch (Exception ex)
        {
            Logger.Error("System Info Collector", "Error while getting cpu name from windows: " + ex.Message);
            return null;
        }
    }

    protected override ulong? GetRamBytesInternal()
    {
        try
        {
            if (_cachedRamBytes != null)
                return _cachedRamBytes;

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
    }
}