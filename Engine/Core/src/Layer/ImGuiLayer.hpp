#pragma once

#include "Window/Window.hpp"

namespace MCEngine
{

class ImGuiLayer : public Layer
{
public:
    ImGuiLayer(std::shared_ptr<Window> window);
    ~ImGuiLayer() override = default;

    void OnAttach() override;
    void OnDetach() override;

public:
    void OnEvent(Event &event) override;
    void OnUpdate(float deltaTime) override;

private:
    std::shared_ptr<Window> m_Window;
    std::string m_GuiFilePath;

private:
    void Begin();
    void BeginDockSpace();

    void End();
    void EndDockSpace();
};

} // namespace MCEngine