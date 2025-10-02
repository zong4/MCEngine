#pragma once

#include "Scene/FullScene.hpp"
#include "Scene/GeometryScene.hpp"
#include "Scene/InstanceScene.hpp"
#include "Script/CameraController.hpp"

namespace MCEditor
{

class EditorLayer : public MCEngine::ImGuiLayer
{

public:
    EditorLayer(const std::shared_ptr<MCEngine::Window> &windowPtr);
    virtual ~EditorLayer() override;

public:
    void OnEvent(MCEngine::Event &event) override;
    void OnUpdate(float deltaTime) override;
    void OnRender() override;

private:
    // Camera
    entt::registry m_Registry = {};
    std::shared_ptr<CameraController> m_CameraPtr;

    // Scene
    entt::entity m_SelectedEntity = entt::null;
    std::unique_ptr<MCEngine::Scene> m_ScenePtr;

    // Scene Panel
    bool m_SceneFocused = false;
    std::unique_ptr<MCEngine::FrameBuffer> m_SceneFBOPtr;
    std::unique_ptr<MCEngine::FrameBuffer> m_SceneMultisampleFBOPtr;

    // Game Panel
    bool m_GameFocused = false;
    std::unique_ptr<MCEngine::FrameBuffer> m_GameFBOPtr;
    std::unique_ptr<MCEngine::FrameBuffer> m_GameMultisampleFBOPtr;

protected:
    // Init
    void InitCamera(const std::shared_ptr<MCEngine::Window> &windowPtr);
    void InitScenePanel();
    void InitGamePanel();

    // Render
    void Begin() override;

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