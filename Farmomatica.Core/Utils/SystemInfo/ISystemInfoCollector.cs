namespace Farmomatica.Core.Utils.SystemInfo;

public interface ISystemInfoCollector
{
    string GetCpuName() => "Unkown CPU";
    ulong GetRamBytes() => 0UL;
}