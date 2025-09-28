#pragma once

#include "Window/Window.hpp"

namespace MCEngine
{

class ImGuiLayer : public Layer
{
public:
    ImGuiLayer(std::shared_ptr<Window> windowPtr, const std::string &filePath, const std::string &name = "ImGuiLayer");
    virtual ~ImGuiLayer() override = default;

    void OnAttach() override;
    void OnDetach() override;

public:
    void OnEvent(Event &event) override;
    void OnImGuiRender(float deltaTime) override;

protected:
    std::shared_ptr<Window> m_WindowPtr;
    std::string m_ImGuiFilePath;

protected:
    virtual void Begin(float deltaTime);
    void End();
};

} // namespace MCEngine