#include "EditorLayer.hpp"

#include "Scene/EditorScene.hpp"
#include "Scene/FullScene.hpp"
#include "Scene/GeometryScene.hpp"
#include "Scene/InstanceScene.hpp"
#include "Script/CameraController.hpp"
#include <imgui.h>

MCEditor::EditorLayer::EditorLayer(const std::shared_ptr<MCEngine::Window> &windowPtr)
    : ImGuiLayer(windowPtr, std::string(PROJECT_ROOT) + "/Editor/Configs/imgui.ini", "EditorLayer")
{
    ENGINE_PROFILE_FUNCTION();

    // Scene
    m_EditorScenePtr = std::make_shared<MCEditor::EditorScene>();
    m_ActiveScenePtr = std::make_unique<MCEditor::FullScene>();

    // UI
    m_ScenePanel = std::make_unique<ViewportPanel>(m_EditorScenePtr->GetMainCamera());
    m_GamePanel = std::make_unique<ViewportPanel>(m_ActiveScenePtr->GetMainCamera());
}

MCEditor::EditorLayer::~EditorLayer() {}

void MCEditor::EditorLayer::OnEvent(MCEngine::Event &event)
{
    ENGINE_PROFILE_FUNCTION();

    ImGuiLayer::OnEvent(event);

    if (!event.IsHandled())
    {
        MCEngine::EventDispatcher dispatcher(event);

        dispatcher.Dispatch<MCEngine::KeyEvent>([this](MCEngine::KeyEvent &e) {
            MCEngine::KeyCodeLibrary::GetInstance().SetKeyAction(e.GetKeyCode(), e.GetAction());
            return true;
        });
    }
}

void MCEditor::EditorLayer::OnUpdate(float deltaTime)
{
    ENGINE_PROFILE_FUNCTION();

    if (m_ScenePanel->IsFocused())
    {
        m_EditorScenePtr->Update(deltaTime);
    }

    m_ActiveScenePtr->Update(deltaTime);
}

void MCEditor::EditorLayer::OnRender()
{
    ENGINE_PROFILE_FUNCTION();

    m_ActiveScenePtr->RenderShadowMap();
    m_ScenePanel->Render(m_ActiveScenePtr);
    m_GamePanel->Render(m_ActiveScenePtr);
}

void MCEditor::EditorLayer::RenderImGui()
{
    ENGINE_PROFILE_FUNCTION();

    RenderDockSpace();
    ImGui::End();

    ImGui::Begin("Hierarchy");
    m_HierarchyPanel.OnImGuiRender(m_ActiveScenePtr->GetRegistry());
    ImGui::End();

    ImGui::Begin("Inspector");
    m_InspectorPanel.OnImGuiRender(m_ActiveScenePtr->GetRegistry(), m_HierarchyPanel.GetSelectedEntity());
    ImGui::End();

    ImGui::Begin("File Browser");
    m_FileBrowserPanel.OnImGuiRender(std::string(PROJECT_ROOT) + "Editor/Assets");
    ImGui::End();

    ImGui::Begin("Scene");
    m_ScenePanel->OnImGuiRender();
    ImGui::End();

    ImGui::Begin("Game");
    m_GamePanel->OnImGuiRender();
    ImGui::End();
}

void MCEditor::EditorLayer::RenderDockSpace() const
{
    ENGINE_PROFILE_FUNCTION();

    ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_NoTitleBar |
                                    ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove |
                                    ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus |
                                    ImGuiWindowFlags_MenuBar;

    ImGuiViewport *viewport = ImGui::GetMainViewport();
    ImGui::SetNextWindowPos(viewport->Pos);
    ImGui::SetNextWindowSize(viewport->Size);
    ImGui::SetNextWindowViewport(viewport->ID);

    ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0, 0, 0, 0));
    ImGui::Begin("DockSpace", nullptr, window_flags);
    ImGui::PopStyleColor();

    ImGuiID dockspace_id = ImGui::GetID("DockSpace");
    ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), ImGuiDockNodeFlags_PassthruCentralNode);

    RenderMenuBar();
}

void MCEditor::EditorLayer::RenderMenuBar() const
{
    ENGINE_PROFILE_FUNCTION();

    if (ImGui::BeginMenuBar())
    {
        if (ImGui::BeginMenu("File"))
        {
            if (ImGui::MenuItem("Exit"))
            {
                m_WindowPtr->SetRunning(false);
            }
            ImGui::EndMenu();
        }
        ImGui::EndMenuBar();
    }
}
