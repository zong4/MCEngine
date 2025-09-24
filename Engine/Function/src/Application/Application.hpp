#pragma once

#include "pch.hpp"

namespace MCEngine
{

class Application
{
public:
    Application() { Init(); }
    virtual ~Application() = default;

public:
    void Run();

    void AddLayer(const std::shared_ptr<Layer> &layer) { m_Window->AddLayer(layer); }
    void RemoveLayer(const std::shared_ptr<Layer> &layer) { m_Window->RemoveLayer(layer); }

private:
    std::unique_ptr<Window> m_Window = nullptr;

private:
    void Init();
};

extern std::unique_ptr<Application> CreateApplication();

} // namespace MCEngine