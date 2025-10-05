#include "EditorLayer.hpp"

#include "EditorConfig.hpp"
#include "Scene/SceneManager.hpp"

MCEditor::EditorLayer::EditorLayer(const std::shared_ptr<MCEngine::Window> &window)
    : ImGuiLayer(window, EditorConfig::GetInstance().GetConfigsPath() + "/imgui.ini", "EditorLayer")
{
    ENGINE_PROFILE_FUNCTION();

    m_SceneViewport.SetCamera(SceneManager::GetInstance().GetEditorScene()->GetMainCamera());
}

void MCEditor::EditorLayer::OnEvent(MCEngine::Event &event)
{
    ENGINE_PROFILE_FUNCTION();

    // Capture events in ImGuiLayer first
    ImGuiLayer::OnEvent(event);

    // Store key states in KeyCodeLibrary
    if (!event.IsHandled())
    {
        MCEngine::EventDispatcher dispatcher(event);
        dispatcher.Dispatch<MCEngine::KeyEvent>([this](MCEngine::KeyEvent &e) {
            MCEngine::KeyCodeLibrary::GetInstance().SetKeyAction(e.GetKeyCode(), e.GetAction());
            return false;
        });
    }

    // Handle key events for editor actions
    if (!event.IsHandled())
    {
        MCEngine::EventDispatcher dispatcher(event);
        dispatcher.Dispatch<MCEngine::KeyEvent>(std::function<bool(MCEngine::KeyEvent &)>(
            std::bind(&EditorLayer::OnKeyEvent, this, std::placeholders::_1)));
    }
}

bool MCEditor::EditorLayer::OnKeyEvent(MCEngine::KeyEvent &event)
{
    // Key Pressed for imguizmo type change
    if (event.GetAction() == 1)
    {
        switch (event.GetKeyCode())
        {
        case ENGINE_KEY_Q:
            if (!ImGuizmo::IsUsing())
                m_GizmoType = ImGuizmoType::None;
            break;
        case ENGINE_KEY_W:
            if (!ImGuizmo::IsUsing())
                m_GizmoType = ImGuizmoType::Translate;
            break;
        case ENGINE_KEY_E:
            if (!ImGuizmo::IsUsing())
                m_GizmoType = ImGuizmoType::Rotate;
            break;
        case ENGINE_KEY_R:
            if (!ImGuizmo::IsUsing())
                m_GizmoType = ImGuizmoType::Scale;
            break;
        default:
            break;
        }
    }

    // Key Pressed for editor actions
    if (event.GetAction() == 1)
    {
        bool control = MCEngine::KeyCodeLibrary::GetInstance().IsKeyDown(ENGINE_KEY_LEFT_CONTROL) ||
                       MCEngine::KeyCodeLibrary::GetInstance().IsKeyDown(ENGINE_KEY_RIGHT_CONTROL) ||
                       MCEngine::KeyCodeLibrary::GetInstance().IsKeyDown(ENGINE_KEY_LEFT_SUPER) ||
                       MCEngine::KeyCodeLibrary::GetInstance().IsKeyDown(ENGINE_KEY_RIGHT_SUPER);
        bool shift = MCEngine::KeyCodeLibrary::GetInstance().IsKeyDown(ENGINE_KEY_LEFT_SHIFT) ||
                     MCEngine::KeyCodeLibrary::GetInstance().IsKeyDown(ENGINE_KEY_RIGHT_SHIFT);

        switch (event.GetKeyCode())
        {
        case ENGINE_KEY_N:
            if (control)
                m_Action = EditorAction::NewScene;
            break;
        case ENGINE_KEY_O:
            if (control)
                m_Action = EditorAction::OpenScene;
            break;
        case ENGINE_KEY_S:
            if (control && shift)
                m_Action = EditorAction::SaveSceneAs;
            break;
        default:
            break;
        }
    }

    return true;
}

void MCEditor::EditorLayer::OnUpdate(float deltaTime)
{
    ENGINE_PROFILE_FUNCTION();

    switch (m_Action)
    {
    case EditorAction::NewScene:
        SceneManager::GetInstance().NewExampleScene();
        break;
    case EditorAction::OpenScene:
        SceneManager::GetInstance().OpenSceneDialog();
        break;
    case EditorAction::SaveSceneAs:
        SceneManager::GetInstance().SaveSceneAsDialog();
        break;
    default:
        break;
    }
    m_Action = EditorAction::None;

    if (m_SceneViewport.IsFocused())
    {
        SceneManager::GetInstance().GetEditorScene()->Update(deltaTime);
    }
    SceneManager::GetInstance().GetActiveScene()->Update(deltaTime);
}

void MCEditor::EditorLayer::OnRender()
{
    ENGINE_PROFILE_FUNCTION();

    auto &&sceneManager = SceneManager::GetInstance();

    // Once per frame
    sceneManager.GetActiveScene()->RenderShadowMap();

    // Render viewports
    m_GameViewport.Render(sceneManager.GetActiveScene());
    m_SceneViewport.Render(sceneManager.GetActiveScene());
}

void MCEditor::EditorLayer::RenderImGui()
{
    ENGINE_PROFILE_FUNCTION();

    RenderDockSpace();
    ImGui::End();

    ImGui::Begin("Hierarchy");
    m_HierarchyPanel.OnImGuiRender(SceneManager::GetInstance().GetActiveScene(),
                                   SceneManager::GetInstance().GetSelectedEntity());
    ImGui::End();

    ImGui::Begin("Inspector");
    m_InspectorPanel.OnImGuiRender(SceneManager::GetInstance().GetSelectedEntity());
    ImGui::End();

    ImGui::Begin("File Browser");
    m_FileBrowserPanel.OnImGuiRender();
    ImGui::End();

    ImGui::Begin("Game");
    m_GameViewport.OnImGuiRender();
    ImGui::End();

    ImGui::Begin("Scene");
    m_SceneViewport.OnImGuiRender(SceneManager::GetInstance().GetSelectedEntity(), m_GizmoType);
    SetBlockEvents(!m_SceneViewport.IsFocused() && !m_SceneViewport.IsHovered());
    ImGui::End();
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
                SceneManager::GetInstance().NewExampleScene();
            if (ImGui::MenuItem("Open...", "Ctrl+O"))
                SceneManager::GetInstance().OpenSceneDialog();
            if (ImGui::MenuItem("Save As...", "Ctrl+Shift+S"))
                SceneManager::GetInstance().SaveSceneAsDialog();

            if (ImGui::MenuItem("Exit"))
            {
                m_Window->SetRunning(false);
            }
            ImGui::EndMenu();
        }
        ImGui::EndMenuBar();
    }
}
