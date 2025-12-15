using System;
using System.IO;
using System.Linq;
using System.Runtime.Versioning;

namespace Farmomatica.Core.Utils.SystemInfo;

public class LinuxCollector : ISystemInfoCollector
{
    [SupportedOSPlatform("linux")]
    public string GetCpuName()
    {
        try
        {
            return File.ReadLines("/proc/cpuinfo")
                .FirstOrDefault(line => line.StartsWith("model name"))
                ?.Split(':')[1].Trim();
        }
        catch (Exception ex)
        {
            Console.Error.WriteLine("Error while collecting cpu info from linux: " + ex.Message);
            return "Unknown CPU";
        }
    }

    [SupportedOSPlatform("linux")]
    public ulong GetRamBytes()
    {
        try
        {
            return File.ReadLines("/proc/meminfo")
                .Select(line => line.Split(':')[1].Trim().Split(' '))
                .Select(parts => ulong.Parse(parts[0]) * 1024)
                .FirstOrDefault();
        }
        catch (Exception ex)
        {
            Console.Error.WriteLine("Error while collecting mem info from linux: " + ex.Message);
            return 0UL;
        }
    }
}