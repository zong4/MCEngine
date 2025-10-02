#pragma once

#include "UI/FileBrowserPanel.hpp"
#include "UI/HierarchyPanel.hpp"
#include "UI/InspectorPanel.hpp"
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
    MCEngine::Entity m_Camera;
    entt::registry m_Registry = {};
    std::shared_ptr<MCEngine::Scene> m_ScenePtr;

    // UI
    HierarchyPanel m_HierarchyPanel;
    InspectorPanel m_InspectorPanel;
    FileBrowserPanel m_FileBrowserPanel;
    std::unique_ptr<ViewportPanel> m_ScenePanel;
    std::unique_ptr<ViewportPanel> m_GamePanel;

protected:
    void RenderImGui() override;

private:
    void RenderDockSpace() const;
    void RenderMenuBar() const;
};

} // namespace MCEditor