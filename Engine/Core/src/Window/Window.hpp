#pragma once

#include "Layer/LayerStack.hpp"

namespace MCEngine
{

struct WindowProps
{
public:
    WindowProps(const std::string &title, int width, int height, bool vsync, const glm::vec4 &backgroundColor);

    const std::string &GetTitle() const { return m_Title; }
    int GetWidth() const { return m_Width; }
    int GetHeight() const { return m_Height; }
    bool IsVSync() const { return m_VSync; }
    const glm::vec4 &GetBackgroundColor() const { return m_BackgroundColor; }

    void SetWidth(int width) { m_Width = width; }
    void SetHeight(int height) { m_Height = height; }
    void SetVSync(bool vsync) { m_VSync = vsync; }

    std::string ToString() const;

private:
    std::string m_Title;
    int m_Width;
    int m_Height;
    bool m_VSync;
    glm::vec4 m_BackgroundColor;
};

class Window
{
public:
    Window(const WindowProps &props);
    ~Window();

    void *GetNativeWindowPtr() const { return m_NativeWindowPtr; }
    WindowProps &GetProps() { return m_Props; }
    const WindowProps &GetProps() const { return m_Props; }

    void SetRunning(bool running) { m_Running = running; }

public:
    bool ShouldClose() const;

    void OnEvent(Event &e);
    void Update(float deltaTime);
    void Render(float deltaTime);

    void AddLayer(const std::shared_ptr<Layer> &layer) { m_LayerStack.PushLayer(layer); }
    void RemoveLayer(const std::shared_ptr<Layer> &layer) { m_LayerStack.PopLayer(layer); }

private:
    bool m_Running = true;
    void *m_NativeWindowPtr = nullptr;
    WindowProps m_Props;

    LayerStack m_LayerStack;

private:
    void Init();
    void Shutdown();

    void SetCallbacks();
    void SetVSync(bool enabled);
};

} // namespace MCEngine
