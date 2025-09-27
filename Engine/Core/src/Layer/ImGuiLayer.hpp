#pragma once

#include "Window/Window.hpp"

namespace MCEngine
{

class ImGuiLayer : public Layer
{
public:
    ImGuiLayer(std::shared_ptr<Window> windowPtr);
    ~ImGuiLayer() override = default;

    void OnAttach() override;
    void OnDetach() override;

public:
    void OnEvent(Event &eventRef) override;
    void OnUpdate(float deltaTime) override {}
    void OnRender() override {}
    void OnImGuiRender(float deltaTime) override;

private:
    std::shared_ptr<Window> m_WindowPtr;
    std::string m_GuiFilePath;

private:
    void Begin();
    void End();

    void RenderDockSpace();
};

} // namespace MCEngine