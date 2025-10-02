#pragma once

#include "Scene/FullScene.hpp"
#include "Scene/GeometryScene.hpp"
#include "Scene/InstanceScene.hpp"
#include "Script/CameraController.hpp"
#include "UI/ViewportPanel.hpp"

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
    std::shared_ptr<MCEngine::Scene> m_ScenePtr;

    // Panels
    std::unique_ptr<ViewportPanel> m_ScenePanel;
    std::unique_ptr<ViewportPanel> m_GamePanel;

protected:
    // Init
    void InitCamera(const std::shared_ptr<MCEngine::Window> &windowPtr);

    // Render
    void Begin() override;

private:
    void BeginDockSpace() const;
    void EndDockSpace() const;
    void RenderMenuBar() const;
    void RenderHierarchyPanel();
    void DrawEntityNode(entt::entity entity);
    void RenderInspectorPanel();
    void RenderFileBrowserPanel();
    void RenderFileBrowser(const std::filesystem::path &directory);
};

} // namespace MCEditor