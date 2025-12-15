using System;
using System.Diagnostics;
using System.Runtime.Versioning;

namespace Farmomatica.Core.Utils.SystemInfo;

[SupportedOSPlatform("macOS")]
public class MacCollector : ISystemInfoCollector
{
    private static string RunSysctl(string fileName, string key)
    {
        Process proc = new()
        {
            StartInfo = new ProcessStartInfo
            {
                FileName = fileName,
                Arguments = key,
                RedirectStandardOutput = true,
                UseShellExecute = false,
                CreateNoWindow = true,
            }
        };

        proc.Start();
        string output = proc.StandardOutput.ReadToEnd();
        proc.WaitForExit();

        return output;
    }

    public string GetCpuName()
    {
        try
        {
            return RunSysctl("sysctl", "-n machdep.cpu.brand_string");
        }
        catch (Exception ex)
        {
            Console.Error.WriteLine("Error while collecting cpu info from macos: " + ex.Message);
            return "Unknown CPU";
        }
    }

    public ulong GetRamBytes()
    {
        try
        {
            return ulong.TryParse(RunSysctl("sysctl", "-n hw.memsize"), out ulong value) ? value : 0;
        }
        catch (Exception ex)
        {
            Console.Error.WriteLine("Error while collecting ram info from macos: " + ex.Message);
            return 0UL;
        }
    }
}