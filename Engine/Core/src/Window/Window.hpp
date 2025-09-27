#pragma once

#include "pch.hpp"

#include "Layer/LayerStack.hpp"

namespace MCEngine
{

struct WindowProps
{
    std::string Title;
    int Width;
    int Height;
    bool VSync;
    float BackgroundColor[4];

public:
    WindowProps(int width, int height, std::string title, bool vsync, float backgroundColor[4]);

    std::string ToString() const;
};

class Window
{
public:
    Window(WindowProps props);
    ~Window();

    void *GetNativeWindowPtr() const { return m_NativeWindowPtr; }
    const WindowProps &GetProps() const { return m_Props; }

    void SetRunning(bool running) { m_Running = running; }

public:
    bool ShouldClose() const;

    void OnEvent(Event &e);
    void PreUpdate();
    void Update(float deltaTime);
    void Render(float deltaTime);
    void PostUpdate();

    void AddLayer(const std::shared_ptr<Layer> &layer) { m_LayerStack.PushLayer(layer); }
    void RemoveLayer(const std::shared_ptr<Layer> &layer) { m_LayerStack.PopLayer(layer); }

private:
    bool m_Running = true;
    void *m_NativeWindowPtr = nullptr;
    WindowProps m_Props;

    LayerStack m_LayerStack;

private:
    void Init();
    void SetCallbacks();
    void SetVSync(bool enabled);

    void Shutdown();
};

} // namespace MCEngine
