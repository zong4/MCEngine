#pragma once

#include <Function.hpp>

namespace MCEditor
{

class EditorLayer : public MCEngine::ImGuiLayer
{

public:
    EditorLayer(std::shared_ptr<MCEngine::Window> windowPtr);

public:
    void OnEvent(MCEngine::Event &event) override;
    void OnUpdate(float deltaTime) override;
    void OnRender() override;

private:
    std::unique_ptr<MCEngine::Scene> m_Scene;
    entt::entity m_SelectedEntity = entt::null;

    std::unique_ptr<MCEngine::FrameBuffer> m_FrameBuffer;

protected:
    void Begin(float deltaTime) override;

private:
    void BeginDockSpace();
    void EndDockSpace();

    void RenderMenuBar();
    void RenderHierarchy();
    void DrawEntityNode(entt::entity entity);
    void RenderInspector();
    void RenderScene();
};

} // namespace MCEditor