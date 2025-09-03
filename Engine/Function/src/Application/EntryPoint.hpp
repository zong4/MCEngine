#pragma once

#include "Application.hpp"

int main(int argc, char **argv)
{
    auto app = CreateApplication();
    app->Run();
    return 0;
}