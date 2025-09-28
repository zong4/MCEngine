#pragma once

#include <Function.hpp>

namespace MCEngine
{

class EditorLayer : public ImGuiLayer
{

public:
    EditorLayer(std::shared_ptr<Window> windowPtr);

public:
    void OnEvent(Event &event) override;
    void OnUpdate(float deltaTime) override;
    void OnRender() override;

private:
    std::shared_ptr<Scene> m_Scene;

protected:
    void Begin(float deltaTime) override;

private:
    void BeginDockSpace();
    void RenderMenuBar();
    void EndDockSpace();
};

} // namespace MCEngine