#pragma once

#include "pch.hpp"

namespace MCEngine
{

class Application
{
public:
    virtual ~Application() = default;
    void Run();

private:
    std::unique_ptr<Window> m_Window = nullptr;
};

extern std::unique_ptr<Application> CreateApplication();

} // namespace MCEngine