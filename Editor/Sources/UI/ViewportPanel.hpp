#pragma once

#include <Function.hpp>
#include <imgui.h>
// After import imgui
#include <ImGuizmo.h>

namespace MCEditor
{

enum class ImGuizmoType
{
    None = -1,
    Translate = ImGuizmo::OPERATION::TRANSLATE,
    Rotate = ImGuizmo::OPERATION::ROTATE,
    Scale = ImGuizmo::OPERATION::SCALE
};

class ViewportPanel
{
public:
    ViewportPanel();
    ~ViewportPanel() = default;

    // Getters
    bool IsFocused() const { return m_Focused; }
    bool IsHovered() const { return m_Hovered; }
    glm::vec2 GetViewportPos() const { return m_ViewportPos; }
    glm::vec2 GetViewportSize() const { return m_ViewportSize; }

public:
    void Render(MCEngine::Entity camera, std::shared_ptr<MCEngine::Scene> scene) const;
    void OnImGuiRender(MCEngine::Entity selectedEntity, ImGuizmoType gizmoType);

private:
    bool m_Focused = false;
    bool m_Hovered = false;
    bool m_ViewportDirty = false;
    glm::vec2 m_ViewportPos = {0.0f, 0.0f};
    glm::vec2 m_ViewportSize = {0.0f, 0.0f};
    std::unique_ptr<MCEngine::FrameBuffer> m_FBOPtr;
    std::unique_ptr<MCEngine::FrameBuffer> m_MultisampleFBOPtr;
};

} // namespace MCEditor