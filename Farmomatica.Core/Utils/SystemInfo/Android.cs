using System;
using System.IO;
using System.Linq;
using System.Runtime.Versioning;

namespace Farmomatica.Core.Utils.SystemInfo;

[SupportedOSPlatform("android")]
public class AndroidCollector : ISystemInfoCollector
{
    public string GetCpuName()
    {
        try
        {
            return File.ReadLines("/proc/cpuinfo")
                .FirstOrDefault(line =>
                    line.StartsWith("Hardware") ||
                    line.StartsWith("model name") ||
                    line.StartsWith("Processor"))
                ?.Split(':')[1].Trim();
        }
        catch (Exception ex)
        {
            Console.Error.WriteLine("Error while collecting cpu info from android: " + ex.Message);
            return "Unknown CPU";
        }
    }

    public ulong GetRamBytes()
    {
        try
        {
            return ulong.Parse(
                File.ReadLines("/proc/meminfo")
                    .First(line => line.StartsWith("MemTotal:"))
                    .Split(' ', StringSplitOptions.RemoveEmptyEntries)[1]
            ) * 1024;
        }
        catch (Exception ex)
        {
            Console.Error.WriteLine("Error while collecting mem info from android: " + ex.Message);
            return 0UL;
        }
    }
}