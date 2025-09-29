#pragma once

#include <Function.hpp>

namespace MCEditor
{

class EditorLayer : public MCEngine::ImGuiLayer
{

public:
    EditorLayer(std::shared_ptr<MCEngine::Window> windowPtr);
    virtual ~EditorLayer() override;

public:
    void OnEvent(MCEngine::Event &event) override;
    void OnUpdate(float deltaTime) override;
    void OnRender() override;

private:
    // Camera
    MCEngine::TransformComponent *m_TransformPtr = nullptr;
    MCEngine::CameraComponent *m_CameraPtr = nullptr;
    float m_CameraMoveSpeed = 1.0f;
    float m_CameraRotateSpeed = 15.0f;

    // Scene
    std::unique_ptr<MCEngine::Scene> m_ScenePtr;
    entt::entity m_SelectedEntity = entt::null;
    std::unique_ptr<MCEngine::FrameBuffer> m_FrameBufferPtr;

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