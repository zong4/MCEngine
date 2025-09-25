#pragma once

#include "pch.hpp"

namespace MCEngine
{

class Application
{
public:
    Application(WindowProps props) { Init(props); }
    virtual ~Application() = default;

    const Application &Get() const { return *this; }
    const Window &GetWindow() const { return *m_Window; }

public:
    virtual void Run();

private:
    std::unique_ptr<Window> m_Window = nullptr;

protected:
    void AddLayer(const std::shared_ptr<Layer> &layer) { m_Window->AddLayer(layer); }
    void RemoveLayer(const std::shared_ptr<Layer> &layer) { m_Window->RemoveLayer(layer); }

private:
    void Init(WindowProps props);
};

extern std::unique_ptr<Application> CreateApplication();

} // namespace MCEngine