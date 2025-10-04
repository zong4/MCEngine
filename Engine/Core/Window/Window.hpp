#pragma once

#include "Layer/LayerStack.hpp"
#include "Renderer/RendererAPIProperty.hpp"
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
    void *GetNativeWindow() const { return m_NativeWindow; }
    WindowProperty &GetProperty() { return m_Property; }
    const WindowProperty &GetProperty() const { return m_Property; }
    const RendererAPIProperty &GetRendererAPIProperty() const { return m_RendererAPIProperty; }

    // Setters
    void SetRunning(bool running) { m_Running = running; }
    void SetVSync(bool enabled);

public:
    // Main loop
    void OnEvent(Event &e);
    void Update(float deltaTime);
    void Render();

    // Layer management
    void AddLayer(const std::shared_ptr<Layer> &layer) { m_LayerStack.PushLayer(layer); }
    void RemoveLayer(const std::shared_ptr<Layer> &layer) { m_LayerStack.PopLayer(layer); }

private:
    bool m_Running = true;
    void *m_NativeWindow = nullptr;
    WindowProperty m_Property;

    // Renderer
#ifdef __APPLE__
    RendererAPIProperty m_RendererAPIProperty = RendererAPIProperty(RendererAPI::OpenGL, 4, 1);
#else
    RendererAPIProperty m_RendererAPIProperty = RendererAPIProperty(RendererAPI::OpenGL, 4, 2);
#endif
    LayerStack m_LayerStack;

private:
    // Initialization
    void Init();
    void SetCallbacks();

    // Cleanup
    void Shutdown();
};

} // namespace MCEngine
