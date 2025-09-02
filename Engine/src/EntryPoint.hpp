#pragma once

#include "pch.hpp"

#include "Application.hpp"

int main(int argc, char **argv)
{
    auto app = CreateApplication();
    app->Run();
    return 0;
}