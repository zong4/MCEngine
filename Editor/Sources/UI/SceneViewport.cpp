#include "SceneViewport.hpp"

#include "Manager/SceneManager.hpp"
#include <imgui.h>
// After import imgui
#include "ImGuizmo/ImGuizmo.h"

MCEditor::SceneViewport::SceneViewport()
{
    ENGINE_PROFILE_FUNCTION();

    m_Camera = SceneManager::GetInstance().GetEditorScene()->GetMainCamera();
}

void MCEditor::SceneViewport::SetGizmoType(ImGuizmoType type)
{
    if (!ImGuizmo::IsUsing())
        m_GizmoType = type;
}

void MCEditor::SceneViewport::Render()
{
    ENGINE_PROFILE_FUNCTION();

    if (m_ViewportDirty)
    {
        m_Camera.GetComponent<MCEngine::CameraComponent>().Resize(m_ViewportSize.x, m_ViewportSize.y);
        m_FBO->Resize((int)m_ViewportSize.x, (int)m_ViewportSize.y);
        m_MultisampleFBO->Resize((int)m_ViewportSize.x, (int)m_ViewportSize.y);
        m_EntityPickingFBO->Resize((int)m_ViewportSize.x, (int)m_ViewportSize.y);
        LOG_EDITOR_TRACE("SceneViewport resized to: (" + std::to_string((int)m_ViewportSize.x) + ", " +
                         std::to_string((int)m_ViewportSize.y) + ")");

        m_ViewportDirty = false;
    }

    m_MultisampleFBO->Bind();
    MCEngine::RendererCommand::Clear();
    SceneManager::GetInstance().GetActiveScene()->Render(m_Camera);
    m_MultisampleFBO->Blit(m_FBO->GetRendererID());
    m_MultisampleFBO->Unbind();

    m_EntityPickingFBO->Bind();
    MCEngine::RendererCommand::Clear();
    SceneManager::GetInstance().GetActiveScene()->RenderColorID(m_Camera);
    m_EntityPickingFBO->Unbind();
}

void MCEditor::SceneViewport::OnImGuiRender()
{
    ENGINE_PROFILE_FUNCTION();

    m_Focused = ImGui::IsWindowFocused();
    m_Hovered = ImGui::IsWindowHovered();
    ImVec2 viewportSize = ImGui::GetContentRegionAvail();
    if (viewportSize.x > 0 && viewportSize.y > 0)
    {
        if (viewportSize.x != m_ViewportSize.x || viewportSize.y != m_ViewportSize.y)
        {
            m_ViewportDirty = true;
            m_ViewportSize = {viewportSize.x, viewportSize.y};
        }
    }
    ImGui::Image((ImTextureID)(intptr_t)m_FBO->GetTexture()->GetRendererID(), viewportSize, ImVec2(0, 1), ImVec2(1, 0));

    RenderGizmos();
    PickEntity(); // After RenderGizmos to avoid conflict with ImGuizmo
}

void MCEditor::SceneViewport::RenderGizmos()
{
    ENGINE_PROFILE_FUNCTION();

    auto &&selectedEntity = SceneManager::GetInstance().GetSelectedEntity();
    if (selectedEntity && m_GizmoType != ImGuizmoType::None)
    {
        ImGuizmo::BeginFrame();
        ImGuizmo::SetOrthographic(false);
        ImGuizmo::SetDrawlist();

        // ImGuizmo rect
        ImGuizmo::SetRect(ImGui::GetWindowPos().x + ImGui::GetWindowContentRegionMin().x,
                          ImGui::GetWindowPos().y + ImGui::GetWindowContentRegionMin().y, m_ViewportSize.x,
                          m_ViewportSize.y);

        // Camera
        const glm::mat4 &cameraProjection = m_Camera.GetComponent<MCEngine::CameraComponent>().GetProjectionMatrix();
        const glm::mat4 &cameraView = m_Camera.GetComponent<MCEngine::TransformComponent>().GetViewMatrix();

        // Entity transform
        auto &&transformComponent = selectedEntity.GetComponent<MCEngine::TransformComponent>();
        glm::mat4 transform = transformComponent.GetTransformMatrix();

        ImGuizmo::OPERATION gizmoOperation;
        switch (m_GizmoType)
        {
        case ImGuizmoType::Translate:
            gizmoOperation = ImGuizmo::OPERATION::TRANSLATE;
            break;
        case ImGuizmoType::Rotate:
            gizmoOperation = ImGuizmo::OPERATION::ROTATE;
            break;
        case ImGuizmoType::Scale:
            gizmoOperation = ImGuizmo::OPERATION::SCALE;
            break;
        default:
            gizmoOperation = ImGuizmo::OPERATION::TRANSLATE;
            break;
        }

        // Snapping
        bool snap = ImGui::IsKeyDown(ImGuiKey_LeftShift) || ImGui::IsKeyDown(ImGuiKey_RightShift);
        float snapValue = 0.5f; // Snap to 0.5m for translation/scale
        if (gizmoOperation == ImGuizmo::OPERATION::ROTATE)
            snapValue = 45.0f; // Snap to 45 degrees for rotation
        float snapValues[3] = {snapValue, snapValue, snapValue};
        ImGuizmo::Manipulate(glm::value_ptr(cameraView), glm::value_ptr(cameraProjection), gizmoOperation,
                             ImGuizmo::LOCAL, glm::value_ptr(transform), nullptr, snap ? snapValues : nullptr);

        if (ImGuizmo::IsUsing())
        {
            glm::vec3 position, rotation, scale;
            MCEngine::Math::DecomposeTransform(transform, position, rotation, scale);
            transformComponent.SetPosition(position);
            transformComponent.SetRotation(glm::degrees(rotation));
            transformComponent.SetScale(scale);
        }
    }
}

void MCEditor::SceneViewport::PickEntity()
{
    ENGINE_PROFILE_FUNCTION();

    ImVec2 mouseInViewport = {ImGui::GetMousePos().x - ImGui::GetWindowPos().x - ImGui::GetWindowContentRegionMin().x,
                              ImGui::GetMousePos().y - ImGui::GetWindowPos().y - ImGui::GetWindowContentRegionMin().y};
    if (m_Hovered && !ImGuizmo::IsUsing() && ImGui::IsMouseClicked(ImGuiMouseButton_Left))
    {
        SceneManager::GetInstance().SetSelectedEntity(
            (entt::entity)(m_EntityPickingFBO->PickPixel((int)mouseInViewport.x,
                                                         (int)(m_ViewportSize.y - mouseInViewport.y)) -
                           1));
    }
}
