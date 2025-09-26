#pragma once

#include "pch.hpp"

namespace MCEngine
{

class Application
{
public:
    Application(WindowProps props);
    virtual ~Application();

    virtual void Run();

protected:
    std::shared_ptr<Window> m_Window = nullptr;

protected:
    void AddLayer(const std::shared_ptr<Layer> &layer) { m_Window->AddLayer(layer); }
    void RemoveLayer(const std::shared_ptr<Layer> &layer) { m_Window->RemoveLayer(layer); }

private:
    void Setup(WindowProps props);
};

extern std::unique_ptr<Application> CreateApplication();

} // namespace MCEngine