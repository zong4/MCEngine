#include "Application.hpp"

int main()
{
    // Create the main instance of Remotery.
    // You need only do this once per program.
    Remotery *rmt;
    rmt_CreateGlobalInstance(&rmt);

    // Explicit begin/end for C
    {
        rmt_BeginCPUSample(LogText, 0);
        rmt_LogText("Time me, please!");
        rmt_EndCPUSample();
    }

    auto app = CreateApplication();
    app->Run();

    // Scoped begin/end for C++
    {
        rmt_ScopedCPUSample(LogText, 0);
        rmt_LogText("Time me, too!");
    }

    // Destroy the main instance of Remotery.
    rmt_DestroyGlobalInstance(rmt);
    std::cout << "CPU profile written to cpu_profile.prof\n";
}