#pragma once

#include "UI/FileBrowserPanel.hpp"
#include "UI/HierarchyPanel.hpp"
#include "UI/InspectorPanel.hpp"
#include "UI/ViewportPanel.hpp"

namespace MCEditor
{

enum class EditorAction
{
    None = 0,
    NewScene,
    OpenScene,
    SaveSceneAs
};

class EditorLayer : public MCEngine::ImGuiLayer
{

public:
    EditorLayer(const std::shared_ptr<MCEngine::Window> &window);
    virtual ~EditorLayer() override;

    // Getters
    ImGuizmoType GetGizmoType() const { return m_GizmoType; }

public:
    void OnEvent(MCEngine::Event &event) override;
    void OnUpdate(float deltaTime) override;
    void OnRender() const override;

    bool OnKeyEvent(MCEngine::KeyEvent &event);

private:
    EditorAction m_Action = EditorAction::None;
    ImGuizmoType m_GizmoType = ImGuizmoType::None;
    HierarchyPanel m_HierarchyPanel;
    InspectorPanel m_InspectorPanel;
    FileBrowserPanel m_FileBrowserPanel;
    ViewportPanel m_ScenePanel;
    ViewportPanel m_GamePanel;

protected:
    void RenderImGui() override;

private:
    void RenderDockSpace();
    void RenderMenuBar();
};

} // namespace MCEditor