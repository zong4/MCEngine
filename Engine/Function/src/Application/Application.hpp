#pragma once

#include "pch.hpp"

namespace MCEngine
{

class Application
{
public:
    Application(WindowProps props) { Init(props); }
    virtual ~Application() { Shutdown(); }

    void Run();

protected:
    std::shared_ptr<Window> m_WindowPtr = nullptr;

protected:
    void AddLayer(const std::shared_ptr<Layer> &layer) { m_WindowPtr->AddLayer(layer); }
    void RemoveLayer(const std::shared_ptr<Layer> &layer) { m_WindowPtr->RemoveLayer(layer); }

private:
    void Init(const WindowProps &props);
    void Shutdown();
};

extern std::unique_ptr<Application> CreateApplication();

} // namespace MCEngine