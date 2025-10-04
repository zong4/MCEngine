#include "ViewportPanel.hpp"

#include "Scene/SceneManager.hpp"

MCEditor::ViewportPanel::ViewportPanel()
{
    ENGINE_PROFILE_FUNCTION();

    m_FBOPtr = std::make_unique<MCEngine::FrameBuffer>(MCEngine::FrameBufferType::Color, 1280, 720);
    m_MultisampleFBOPtr = std::make_unique<MCEngine::FrameBuffer>(MCEngine::FrameBufferType::Multisample, 1280, 720, 4);
}

void MCEditor::ViewportPanel::Render(MCEngine::Entity camera, std::shared_ptr<MCEngine::Scene> scene) const
{
    ENGINE_PROFILE_FUNCTION();

    if (m_ViewportDirty)
    {
        if (camera.HasComponent<MCEngine::CameraComponent>())
        {
            camera.GetComponent<MCEngine::CameraComponent>().Resize(m_ViewportSize.x, m_ViewportSize.y);
        }

        m_FBOPtr->Resize((int)m_ViewportSize.x, (int)m_ViewportSize.y);
        m_MultisampleFBOPtr->Resize((int)m_ViewportSize.x, (int)m_ViewportSize.y);
    }

    m_MultisampleFBOPtr->Bind();
    MCEngine::RendererCommand::Clear();
    scene->Render(camera);
    m_MultisampleFBOPtr->Blit(m_FBOPtr->GetRendererID());
    m_MultisampleFBOPtr->Unbind();
}

void MCEditor::ViewportPanel::OnImGuiRender(MCEngine::Entity selectedEntity, ImGuizmoType gizmoType)
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
    ImGui::Image((ImTextureID)(intptr_t)m_FBOPtr->GetTexturePtr()->GetRendererID(), viewportSize, ImVec2(0, 1),
                 ImVec2(1, 0));

    // Gizmos
    if (selectedEntity && gizmoType != ImGuizmoType::None)
    {
        ImGuizmo::BeginFrame();
        ImGuizmo::SetOrthographic(false);
        ImGuizmo::SetDrawlist();

        ImGuizmo::SetRect(ImGui::GetWindowPos().x, ImGui::GetWindowPos().y, m_ViewportSize.x, m_ViewportSize.y);

        // Camera
        auto &&cameraEntity = SceneManager::GetInstance().GetEditorScene()->GetMainCamera();
        const glm::mat4 &cameraProjection =
            cameraEntity.GetComponent<MCEngine::CameraComponent>().GetProjectionMatrix();
        const glm::mat4 &cameraView = cameraEntity.GetComponent<MCEngine::TransformComponent>().GetViewMatrix();

        // Entity transform
        auto &&transformComponent = selectedEntity.GetComponent<MCEngine::TransformComponent>();
        glm::mat4 transform = transformComponent.GetTransformMatrix();

        // Snapping
        bool snap = ImGui::IsKeyDown(ImGuiKey_LeftShift) || ImGui::IsKeyDown(ImGuiKey_RightShift);
        // Snap to 0.5m for translation/scale
        float snapValue = 0.5f;
        // Snap to 45 degrees for rotation
        if ((ImGuizmo::OPERATION)gizmoType == ImGuizmo::OPERATION::ROTATE)
            snapValue = 45.0f;
        float snapValues[3] = {snapValue, snapValue, snapValue};
        ImGuizmo::Manipulate(glm::value_ptr(cameraView), glm::value_ptr(cameraProjection),
                             (ImGuizmo::OPERATION)gizmoType, ImGuizmo::LOCAL, glm::value_ptr(transform), nullptr,
                             snap ? snapValues : nullptr);

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