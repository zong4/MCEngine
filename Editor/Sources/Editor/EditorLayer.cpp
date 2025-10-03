#include "EditorLayer.hpp"

#include "Scene/FullScene.hpp"
#include "Scene/GeometryScene.hpp"
#include "Scene/InstanceScene.hpp"
#include "Script/CameraController.hpp"
#include <imgui.h>

MCEditor::EditorLayer::EditorLayer(const std::shared_ptr<MCEngine::Window> &windowPtr)
    : ImGuiLayer(windowPtr, std::string(PROJECT_ROOT) + "/Editor/Configs/imgui.ini", "EditorLayer")
{
    ENGINE_PROFILE_FUNCTION();

    MCEngine::Entity m_Camera(m_Registry.create(), &m_Registry);
    m_Camera.AddComponent<MCEngine::TransformComponent>();
    m_Camera.AddComponent<MCEngine::CameraComponent>(MCEngine::CameraType::Perspective);
    m_Camera.AddComponent<MCEngine::NativeScriptComponent>().Bind<CameraController>();

    // Scene
    m_ScenePtr = std::make_unique<MCEditor::FullScene>();

    // UI
    m_ScenePanel = std::make_unique<ViewportPanel>(m_Camera);
    m_GamePanel = std::make_unique<ViewportPanel>(m_ScenePtr->GetMainCamera());
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

        m_ScenePtr->OnEvent(event);
    }
}

void MCEditor::EditorLayer::OnUpdate(float deltaTime)
{
    ENGINE_PROFILE_FUNCTION();

    if (m_ScenePanel->IsFocused())
    {
        auto &&view = m_Registry.view<MCEngine::TransformComponent>();
        for (auto &&entity : view)
        {
            auto &&transform = view.get<MCEngine::TransformComponent>(entity);
            transform.UpdateTransformMatrix();
            transform.UpdateViewMatrix();
        }

        m_Registry.view<MCEngine::NativeScriptComponent>().each([&](auto &&entity, auto &&nsc) {
            if (!nsc.Instance)
            {
                nsc.Instance = nsc.InstantiateScript();
                nsc.Instance->SetEntity(MCEngine::Entity{entity, &m_Registry});
                nsc.Instance->OnCreate();
                nsc.Instance->OnStart();
            }
            nsc.Instance->OnUpdate(deltaTime);
        });
    }

    m_ScenePtr->Update(deltaTime);
}

void MCEditor::EditorLayer::OnRender()
{
    ENGINE_PROFILE_FUNCTION();

    m_ScenePtr->RenderShadowMap();
    m_ScenePanel->Render(m_ScenePtr);
    m_GamePanel->Render(m_ScenePtr);
}

void MCEditor::EditorLayer::RenderImGui()
{
    ENGINE_PROFILE_FUNCTION();

    RenderDockSpace();
    ImGui::End();

    ImGui::Begin("Hierarchy");
    m_HierarchyPanel.OnImGuiRender(m_ScenePtr->GetRegistry());
    ImGui::End();

    ImGui::Begin("Inspector");
    m_InspectorPanel.OnImGuiRender(m_ScenePtr->GetRegistry(), m_HierarchyPanel.GetSelectedEntity());
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
