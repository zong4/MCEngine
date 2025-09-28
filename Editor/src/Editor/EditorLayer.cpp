#include "EditorLayer.hpp"

#include <imgui.h>

MCEngine::EditorLayer::EditorLayer(std::shared_ptr<Window> windowPtr)
    : ImGuiLayer(windowPtr, std::string(PROJECT_ROOT) + "/Editor/configs/imgui.ini", "EditorLayer")
{
    ENGINE_PROFILE_FUNCTION();

    TransformComponent squareTransform(glm::vec3(0.0f), glm::vec3(0.0f), glm::vec3(3.0f));
    SpriteRendererComponent squareSprite(VAOLibrary::GetInstance().GetVAO("IdentitySquare"),
                                         glm::vec4(1.0f, 0.7f, 0.8f, 1.0f),
                                         TextureLibrary::GetInstance().GetTexture("02BG"));

    TransformComponent cubeTransform(glm::vec3(0.0f), glm::vec3(0.0f), glm::vec3(1.0f));
    MeshRendererComponent cubeMesh(VAOLibrary::GetInstance().GetVAO("IdentityCube"), glm::vec4(0.0f, 0.0f, 1.0f, 0.8f));

    m_Scene = std::make_shared<Scene>();
    EntityFactory::CreateEntity(m_Scene->GetRegistry(), squareTransform, squareSprite);
    EntityFactory::CreateEntity(m_Scene->GetRegistry(), cubeTransform, cubeMesh);
};

void MCEngine::EditorLayer::OnEvent(Event &event)
{
    ENGINE_PROFILE_FUNCTION();

    EventDispatcher dispatcher(event);
    dispatcher.Dispatch<KeyEvent>([this](KeyEvent &e) {
        KeyCodeLibrary::GetInstance().SetKeyAction(e.GetKeyCode(), e.GetAction());
        return true;
    });

    m_Scene->OnEvent(event);
}

void MCEngine::EditorLayer::OnUpdate(float deltaTime)
{
    ENGINE_PROFILE_FUNCTION();

    m_Scene->Update(deltaTime);
}

void MCEngine::EditorLayer::OnRender()
{
    ENGINE_PROFILE_FUNCTION();

    m_Scene->Render();
}

void MCEngine::EditorLayer::Begin(float deltaTime)
{
    ImGuiLayer::Begin(deltaTime);

    BeginDockSpace();

    ImGui::Begin("Event Info");
    ImGui::Text("Delta Time: %.3f ms/frame (%.1f FPS)", deltaTime * 1000.0f, 1.0f / deltaTime);
    ImGui::Text("Mouse Position: (%.1f, %.1f)", ImGui::GetIO().MousePos.x, ImGui::GetIO().MousePos.y);
    ImGui::Text("Mouse Buttons: Left(%d), Right(%d), Middle(%d)", ImGui::GetIO().MouseDown[0],
                ImGui::GetIO().MouseDown[1], ImGui::GetIO().MouseDown[2]);
    ImGui::End();

    EndDockSpace();
}

void MCEngine::EditorLayer::BeginDockSpace()
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

void MCEngine::EditorLayer::RenderMenuBar()
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

void MCEngine::EditorLayer::EndDockSpace()
{
    ENGINE_PROFILE_FUNCTION();

    ImGui::End();
}