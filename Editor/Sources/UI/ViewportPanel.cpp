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
    if ((int)viewportSize.x != m_FBOPtr->GetWidth() || (int)viewportSize.y != m_FBOPtr->GetHeight())
    {
        m_Camera.GetComponent<MCEngine::CameraComponent>().Resize(viewportSize.x, viewportSize.y);

        m_FBOPtr->Resize((int)viewportSize.x, (int)viewportSize.y);
        m_MultisampleFBOPtr->Resize((int)viewportSize.x, (int)viewportSize.y);
    }
    ImGui::Image((ImTextureID)(intptr_t)m_FBOPtr->GetTexturePtr()->GetRendererID(), viewportSize, ImVec2(0, 1),
                 ImVec2(1, 0));
}