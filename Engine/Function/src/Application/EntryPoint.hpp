#pragma once

#include "Application.hpp"

int main(int argc, char **argv)
{
    EASY_PROFILER_ENABLE;
    profiler::dumpBlocksToFile("Logs/Engine.prof");

    auto app = CreateApplication();
    app->Run();
    return 0;
}