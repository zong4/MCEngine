#include "pch.hpp"
#include <gperftools/profiler.h>

int main()
{
    ProfilerStart("cpu_profile.prof"); // Start sampling

    ProfilerStop(); // Stop sampling
    std::cout << "CPU profile written to cpu_profile.prof\n";
}