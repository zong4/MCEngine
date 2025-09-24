#pragma once

#include "pch.hpp"

#include "Layer/LayerStack.hpp"

namespace MCEngine
{

class Window
{
public:
    Window(int width, int height, std::string title) { Init(width, height, title); }
    ~Window() { Shutdown(); }

    bool IsVSync() const { return m_VSync; }
    void SetVSync(bool enabled);

public:
    bool ShouldClose() const;

    void OnEvent(Event &e);

    void PreUpdate();
    void Update() { m_LayerStack->Update(); }
    void PostUpdate();

    void AddLayer(const std::shared_ptr<Layer> &layer) { m_LayerStack->PushLayer(layer); }
    void RemoveLayer(const std::shared_ptr<Layer> &layer) { m_LayerStack->PopLayer(layer); }

private:
    void *m_Window = nullptr;

    // Parameters
    bool m_VSync = true;
    std::unique_ptr<LayerStack> m_LayerStack = nullptr;

protected:
    void Init(int width, int height, std::string title);
    void Shutdown();

    void SetCallbacks();
};

} // namespace MCEngine
