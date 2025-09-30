#pragma once

#include "Layer/LayerStack.hpp"
#include "WindowProperty.hpp"

namespace MCEngine
{

class Window
{
public:
    Window(const WindowProperty &property);
    ~Window();

    // Getters
    bool IsRunning() const;
    void *GetNativeWindowPtr() const { return m_NativeWindowPtr; }
    WindowProperty &GetProperty() { return m_Property; }
    const WindowProperty &GetProperty() const { return m_Property; }

    // Setters
    void SetRunning(bool running) { m_Running = running; }
    void SetVSync(bool enabled);

public:
    // Main loop
    void OnEvent(Event &e);
    void Update(float deltaTime);
    void Render(float deltaTime);

    // Layer management
    void AddLayer(const std::shared_ptr<Layer> &layer) { m_LayerStack.PushLayer(layer); }
    void RemoveLayer(const std::shared_ptr<Layer> &layer) { m_LayerStack.PopLayer(layer); }

private:
    bool m_Running = true;
    void *m_NativeWindowPtr = nullptr;
    WindowProperty m_Property;

    LayerStack m_LayerStack;

private:
    // Initialization
    void Init();
    void SetCallbacks();

    // Cleanup
    void Shutdown();
};

} // namespace MCEngine
