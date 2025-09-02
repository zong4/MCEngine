#pragma once

#include "pch.hpp"

class Application
{
public:
    virtual ~Application() = default;
    void Run()
    {
        std::cout << "Application is running..." << std::endl;
    }
};

extern std::unique_ptr<Application> CreateApplication();