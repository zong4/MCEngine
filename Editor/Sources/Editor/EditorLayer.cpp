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
    m_EditorScene = std::make_shared<MCEditor::EditorScene>();
    m_ActiveScene = std::make_unique<MCEditor::FullScene>();
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

    if (m_ScenePanel.IsFocused())
    {
        m_EditorScene->Update(deltaTime);
    }

    m_ActiveScene->Update(deltaTime);
}

void MCEditor::EditorLayer::OnRender()
{
    ENGINE_PROFILE_FUNCTION();

    m_ActiveScene->RenderShadowMap();
    m_ScenePanel.Render(m_EditorScene->GetMainCamera(), m_ActiveScene);
    m_GamePanel.Render(m_ActiveScene->GetMainCamera(), m_ActiveScene);
}

void MCEditor::EditorLayer::RenderImGui()
{
    ENGINE_PROFILE_FUNCTION();

    RenderDockSpace();
    ImGui::End();

    ImGui::Begin("Hierarchy");
    m_HierarchyPanel.OnImGuiRender(m_ActiveScene->GetRegistry());
    ImGui::End();

    ImGui::Begin("Inspector");
    m_InspectorPanel.OnImGuiRender({m_HierarchyPanel.GetSelectedEntity(), &m_ActiveScene->GetRegistry()});
    ImGui::End();

    ImGui::Begin("File Browser");
    m_FileBrowserPanel.OnImGuiRender(std::string(PROJECT_ROOT) + "Editor/Assets");
    ImGui::End();

    ImGui::Begin("Scene");
    m_ScenePanel.OnImGuiRender();
    ImGui::End();

    ImGui::Begin("Game");
    m_GamePanel.OnImGuiRender();
    ImGui::End();
}

void MCEditor::EditorLayer::NewScene() { m_ActiveScene = std::make_shared<MCEngine::Scene>(); }

void MCEditor::EditorLayer::OpenScene() const
{
    const char *filters[] = {"*.mcs"};
    std::string defaultPath = std::string(PROJECT_ROOT) + "/Editor/Assets/Scenes/";
    const char *file = tinyfd_openFileDialog("Open Scene", defaultPath.c_str(), 1, filters, nullptr, 0);
    if (file)
    {
        MCEngine::SceneSerializer serializer(m_ActiveScene);
        serializer.Deserialize(file);
    }
}

void MCEditor::EditorLayer::SaveSceneAs() const
{
    const char *filters[] = {"*.mcs"};
    std::string defaultPath = std::string(PROJECT_ROOT) + "/Editor/Assets/Scenes/Untitled";
    const char *file = tinyfd_saveFileDialog("Save Scene As", defaultPath.c_str(), 1, filters, nullptr);

    if (file)
    {
        // Trim whitespace and ensure the file has the correct extension
        std::string filepath = file ? std::string(file) : "";
        filepath.erase(filepath.find_last_not_of(" \n\r\t") + 1);
        if (!filepath.empty() && filepath.substr(filepath.size() - 4) != ".mcs")
            filepath += ".mcs";

        MCEngine::SceneSerializer serializer(m_ActiveScene);
        serializer.Serialize(filepath);
    }
}

void MCEditor::EditorLayer::RenderDockSpace()
{
    ENGINE_PROFILE_FUNCTION();

    // Note: Switch this to true to enable dockspace
    static bool dockspaceOpen = true;
    static bool opt_fullscreen_persistant = true;
    bool opt_fullscreen = opt_fullscreen_persistant;
    static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

    // We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
    // because it would be confusing to have two docking targets within each others.
    ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
    if (opt_fullscreen)
    {
        ImGuiViewport *viewport = ImGui::GetMainViewport();
        ImGui::SetNextWindowPos(viewport->Pos);
        ImGui::SetNextWindowSize(viewport->Size);
        ImGui::SetNextWindowViewport(viewport->ID);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
        window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize |
                        ImGuiWindowFlags_NoMove;
        window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
    }

    // When using ImGuiDockNodeFlags_PassthruCentralNode, DockSpace() will render our background and handle the
    // pass-thru hole, so we ask Begin() to not render a background.
    if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
        window_flags |= ImGuiWindowFlags_NoBackground;

    // Important: note that we proceed even if Begin() returns false (aka window is collapsed).
    // This is because we want to keep our DockSpace() active. If a DockSpace() is inactive,
    // all active windows docked into it will lose their parent and become undocked.
    // We cannot preserve the docking relationship between an active window and an inactive docking, otherwise
    // any change of dockspace/settings would lead to windows being stuck in limbo and never being visible.
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
    ImGui::Begin("DockSpace", &dockspaceOpen, window_flags);
    ImGui::PopStyleVar();

    if (opt_fullscreen)
        ImGui::PopStyleVar(2);

    // DockSpace
    ImGuiIO &io = ImGui::GetIO();
    ImGuiStyle &style = ImGui::GetStyle();
    float minWinSizeX = style.WindowMinSize.x;
    style.WindowMinSize.x = 200.0f; // todo
    if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
    {
        ImGuiID dockspace_id = ImGui::GetID("DockSpace");
        ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
    }
    style.WindowMinSize.x = minWinSizeX;

    RenderMenuBar();
}

void MCEditor::EditorLayer::RenderMenuBar()
{
    ENGINE_PROFILE_FUNCTION();

    if (ImGui::BeginMenuBar())
    {
        if (ImGui::BeginMenu("File"))
        {
            if (ImGui::MenuItem("New", "Ctrl+N"))
                NewScene();

            if (ImGui::MenuItem("Open...", "Ctrl+O"))
                OpenScene();

            if (ImGui::MenuItem("Save As...", "Ctrl+Shift+S"))
                SaveSceneAs();

            if (ImGui::MenuItem("Exit"))
            {
                m_WindowPtr->SetRunning(false);
            }
            ImGui::EndMenu();
        }
        ImGui::EndMenuBar();
    }
}
