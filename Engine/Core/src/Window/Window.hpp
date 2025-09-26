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

    WindowProps() = default;
    WindowProps(int width, int height, std::string title, bool vsync, float backgroundColor[4]);

    std::string ToString() const;
};

class Window
{
public:
    Window(WindowProps props);
    ~Window();

    void *GetNativeWindow() const { return m_NativeWindow; }
    const WindowProps &GetProps() const { return m_Props; }

public:
    bool ShouldClose() const;

    void OnEvent(Event &e);
    void PreUpdate();
    void Update(float deltaTime);
    void PostUpdate();

    void AddLayer(const std::shared_ptr<Layer> &layer) { m_LayerStack->PushLayer(layer); }
    void RemoveLayer(const std::shared_ptr<Layer> &layer) { m_LayerStack->PopLayer(layer); }

private:
    void *m_NativeWindow = nullptr;
    WindowProps m_Props;

    std::unique_ptr<LayerStack> m_LayerStack = nullptr;

private:
    void Init();
    void SetCallbacks();
    void SetVSync(bool enabled);

    void Shutdown();
};

} // namespace MCEngine
