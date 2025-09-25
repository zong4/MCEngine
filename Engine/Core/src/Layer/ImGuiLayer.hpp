#pragma once

#include "Window/Window.hpp"

namespace MCEngine
{

class ImGuiLayer : public Layer
{
public:
    ImGuiLayer(Window *window);
    ~ImGuiLayer() override = default;

public:
    void OnEvent(Event &event) override;

    void OnAttach() override;
    void OnUpdate() override;
    void OnDetach() override;

private:
    Window *m_Window;

private:
    void Begin();
    void End();
};

} // namespace MCEngine