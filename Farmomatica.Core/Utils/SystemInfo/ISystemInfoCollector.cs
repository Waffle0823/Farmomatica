namespace Farmomatica.Core.Utils.SystemInfo;

public interface ISystemInfoCollector
{
    string GetCpuName() => "Unknown CPU";
    ulong GetRamBytes() => 0UL;
}