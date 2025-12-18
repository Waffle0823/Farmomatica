namespace Farmomatica.Core.Utils.SystemInfo;

public abstract class SystemInfoCollector
{
    public string GetCpuName() => GetCpuNameInternal() ?? "Unknown CPU";
    public ulong GetRamBytes() => GetRamBytesInternal() ?? 0UL;

    protected abstract string GetCpuNameInternal();
    protected abstract ulong? GetRamBytesInternal();
}