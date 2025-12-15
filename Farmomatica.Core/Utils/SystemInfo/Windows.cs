using System;
using System.Runtime.InteropServices;
using System.Runtime.Versioning;
using Microsoft.Win32;

namespace Farmomatica.Core.Utils.SystemInfo;

[SupportedOSPlatform("windows")]
public partial class WindowsCollector : ISystemInfoCollector
{
    [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Auto)]
    private struct MemoryMarshal
    {
        public uint dwLength;
        public uint dwMemoryLoad;
        public ulong ullTotalPhys;
        public ulong ullAvailPhys;
        public ulong ullTotalPageFile;
        public ulong ullAvailPageFile;
        public ulong ullTotalVirtual;
        public ulong ullAvailVirtual;
        public ulong ullAvailExtendedVirtual;
    }

    [LibraryImport("kernel32.dll", SetLastError = true)]
    [return: MarshalAs(UnmanagedType.Bool)]
    private static partial bool GlobalMemoryStatusEx(ref MemoryMarshal lpBuffer);

    public string GetCpuName()
    {
        try
        {
            using RegistryKey key = Registry.LocalMachine.OpenSubKey(
                @"HARDWARE\DESCRIPTION\System\CentralProcessor\0"
            );

            return key?.GetValue("ProcessorNameString") as string ?? "Unknown CPU";
        }
        catch (Exception ex)
        {
            Console.Error.WriteLine("Error while collecting cpu info from windows: " + ex.Message);
            return "Unknown CPU";
        }
    }

    public ulong GetRamBytes()
    {
        MemoryMarshal memStatus = new()
        {
            dwLength = (uint)Marshal.SizeOf<MemoryMarshal>()
        };

        return GlobalMemoryStatusEx(ref memStatus) ? memStatus.ullTotalPhys : 0UL;
    }
}