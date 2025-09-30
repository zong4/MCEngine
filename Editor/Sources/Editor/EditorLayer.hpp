#pragma once

#include "Scene/SampleScene.hpp"

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
    bool m_SceneFocused = false;
    std::unique_ptr<MCEngine::Scene> m_ScenePtr;
    entt::entity m_SelectedEntity = entt::null;
    std::unique_ptr<MCEngine::FrameBuffer> m_SceneFBOPtr;
    std::unique_ptr<MCEngine::FrameBuffer> m_SceneMultisampleFBOPtr;

    // Game
    bool m_GameFocused = false;
    std::unique_ptr<MCEngine::FrameBuffer> m_GameFBOPtr;
    std::unique_ptr<MCEngine::FrameBuffer> m_GameMultisampleFBOPtr;

protected:
    void Begin(float deltaTime) override;

    void InitCamera(std::shared_ptr<MCEngine::Window> windowPtr);
    void InitScenePanel();
    void InitGamePanel();

private:
    void BeginDockSpace() const;
    void EndDockSpace() const;
    void RenderMenuBar() const;
    void RenderHierarchyPanel();
    void DrawEntityNode(entt::entity entity);
    void RenderInspectorPanel();
    void RenderScenePanel();
    void RenderGamePanel();
    void RenderFileBrowserPanel();
    void RenderFileBrowser(const std::filesystem::path &directory);
};

} // namespace MCEditor