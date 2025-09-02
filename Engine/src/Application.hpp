#pragma once

#include "pch.hpp"

#include "Window.hpp"

class Application
{
public:
    virtual ~Application() = default;
    void Run()
    {
        m_Window = std::make_unique<Window>(800, 600, "MC Engine");
        while (!m_Window->ShouldClose())
        {
            m_Window->Update();
        }
    }

private:
    std::unique_ptr<Window> m_Window;
};

extern std::unique_ptr<Application> CreateApplication();