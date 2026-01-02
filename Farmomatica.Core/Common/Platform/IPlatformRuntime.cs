namespace Farmomatica.Core.Common.Platform;

public interface IPlatformRuntime
{
    void Initialize();
    void Update();
    void Shutdown();
}