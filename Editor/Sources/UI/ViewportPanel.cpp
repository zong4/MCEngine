#include "ViewportPanel.hpp"

#include <imgui.h>

MCEditor::ViewportPanel::ViewportPanel(MCEngine::Entity camera) : m_Camera(camera)
{
    ENGINE_PROFILE_FUNCTION();

    m_FBOPtr = std::make_unique<MCEngine::FrameBuffer>(MCEngine::FrameBufferType::Color, 1280, 720);
    m_MultisampleFBOPtr = std::make_unique<MCEngine::FrameBuffer>(MCEngine::FrameBufferType::Multisample, 1280, 720, 4);
}

void MCEditor::ViewportPanel::Render(std::shared_ptr<MCEngine::Scene> scene)
{
    ENGINE_PROFILE_FUNCTION();

    if (m_ViewportDirty)
    {
        if (m_Camera.HasComponent<MCEngine::CameraComponent>())
        {
            m_Camera.GetComponent<MCEngine::CameraComponent>().Resize(m_ViewportSize.x, m_ViewportSize.y);
        }

        m_FBOPtr->Resize((int)m_ViewportSize.x, (int)m_ViewportSize.y);
        m_MultisampleFBOPtr->Resize((int)m_ViewportSize.x, (int)m_ViewportSize.y);
    }

    m_MultisampleFBOPtr->Bind();
    MCEngine::RendererCommand::Clear();
    scene->Render(m_Camera);
    m_MultisampleFBOPtr->Blit(m_FBOPtr->GetRendererID());
    m_MultisampleFBOPtr->Unbind();
}

void MCEditor::ViewportPanel::OnImGuiRender()
{
    ENGINE_PROFILE_FUNCTION();

    m_Focused = ImGui::IsWindowFocused();

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
}