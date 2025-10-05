#pragma once

#include <Function.hpp>

namespace MCEditor
{

enum class ImGuizmoType
{
    None = -1,
    Translate = 1,
    Rotate = 2,
    Scale = 3
};

class SceneViewport
{
public:
    SceneViewport();
    ~SceneViewport() = default;

    // Setters
    void SetGizmoType(ImGuizmoType type);

    // Getters
    bool IsFocused() const { return m_Focused; }
    bool IsHovered() const { return m_Hovered; }
    glm::vec2 GetViewportSize() const { return m_ViewportSize; }

public:
    void Render();
    void OnImGuiRender();

private:
    bool m_Focused = false;
    bool m_Hovered = false;
    bool m_ViewportDirty = false;
    glm::vec2 m_ViewportSize = {0.0f, 0.0f};

    // Rendering
    MCEngine::Entity m_Camera;
    std::unique_ptr<MCEngine::FrameBuffer> m_FBO =
        std::make_unique<MCEngine::FrameBuffer>(MCEngine::FrameBufferType::Color, 1280, 720);
    std::unique_ptr<MCEngine::FrameBuffer> m_MultisampleFBO =
        std::make_unique<MCEngine::FrameBuffer>(MCEngine::FrameBufferType::Multisample, 1280, 720, 4);
    std::unique_ptr<MCEngine::FrameBuffer> m_EntityPickingFBO =
        std::make_unique<MCEngine::FrameBuffer>(MCEngine::FrameBufferType::Integer, 1280, 720);

    // ImGuizmo
    ImGuizmoType m_GizmoType = ImGuizmoType::Translate;

private:
    void RenderGizmos();
    void PickEntity();
};

} // namespace MCEditor