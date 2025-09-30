#pragma once

#include "Window/Window.hpp"

namespace MCEngine
{

class ImGuiLayer : public Layer
{
public:
    ImGuiLayer(const std::shared_ptr<Window> &windowPtr, const std::string &filePath,
               const std::string &name = "ImGuiLayer");
    virtual ~ImGuiLayer() override = default;

public:
    // Main loop
    void OnEvent(Event &event) override;
    void OnImGuiRender() override;

    // Called by LayerStack
    void OnAttach() override;
    void OnDetach() override;

protected:
    std::shared_ptr<Window> m_WindowPtr;
    std::string m_ImGuiFilePath;

protected:
    virtual void Begin();
    void End();
};

} // namespace MCEngine