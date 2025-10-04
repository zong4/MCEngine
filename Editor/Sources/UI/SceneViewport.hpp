#pragma once

#include <Function.hpp>
#include <imgui.h>
// After import imgui
#include "ImGuizmo/ImGuizmo.h"

namespace MCEditor
{

enum class ImGuizmoType
{
    None = -1,
    Translate = ImGuizmo::OPERATION::TRANSLATE,
    Rotate = ImGuizmo::OPERATION::ROTATE,
    Scale = ImGuizmo::OPERATION::SCALE
};

class SceneViewport
{
public:
    SceneViewport() = default;
    ~SceneViewport() = default;

    // Getters
    bool IsFocused() const { return m_Focused; }
    bool IsHovered() const { return m_Hovered; }
    glm::vec2 GetViewportSize() const { return m_ViewportSize; }

    // Setters
    void SetCamera(MCEngine::Entity camera) { m_Camera = camera; }

public:
    void Render(std::shared_ptr<MCEngine::Scene> scene) const;
    void OnImGuiRender(MCEngine::Entity selectedEntity, ImGuizmoType gizmoType);

private:
    MCEngine::Entity m_Camera;
    bool m_Focused = false;
    bool m_Hovered = false;
    bool m_ViewportDirty = false;
    glm::vec2 m_ViewportSize = {0.0f, 0.0f};
    std::unique_ptr<MCEngine::FrameBuffer> m_FBO =
        std::make_unique<MCEngine::FrameBuffer>(MCEngine::FrameBufferType::Color, 1280, 720);
    std::unique_ptr<MCEngine::FrameBuffer> m_MultisampleFBO =
        std::make_unique<MCEngine::FrameBuffer>(MCEngine::FrameBufferType::Multisample, 1280, 720, 4);
    std::unique_ptr<MCEngine::FrameBuffer> m_EntityPickingFBO =
        std::make_unique<MCEngine::FrameBuffer>(MCEngine::FrameBufferType::Integer, 1280, 720);
};

} // namespace MCEditor