#pragma once

#include "pch.hpp"

class Window;

class Application
{
public:
    virtual ~Application() = default;
    void Run();

private:
    std::unique_ptr<Window> m_Window = nullptr;
};

extern std::unique_ptr<Application> CreateApplication();