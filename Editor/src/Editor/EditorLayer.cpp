#include "EditorLayer.hpp"

#include <imgui.h>

MCEditor::EditorLayer::EditorLayer(std::shared_ptr<MCEngine::Window> windowPtr)
    : ImGuiLayer(windowPtr, std::string(PROJECT_ROOT) + "/Editor/configs/imgui.ini", "EditorLayer")
{
    ENGINE_PROFILE_FUNCTION();

    MCEngine::TransformComponent squareTransform(glm::vec3(0.0f), glm::vec3(0.0f), glm::vec3(3.0f));
    MCEngine::SpriteRendererComponent squareSprite(MCEngine::VAOLibrary::GetInstance().GetVAO("IdentitySquare"),
                                                   glm::vec4(1.0f, 0.7f, 0.8f, 1.0f),
                                                   MCEngine::TextureLibrary::GetInstance().GetTexture("02BG"));

    MCEngine::TransformComponent cubeTransform(glm::vec3(0.0f), glm::vec3(0.0f), glm::vec3(1.0f));
    MCEngine::MeshRendererComponent cubeMesh(MCEngine::VAOLibrary::GetInstance().GetVAO("IdentityCube"),
                                             glm::vec4(0.0f, 0.0f, 1.0f, 0.8f));

    m_Scene = std::make_shared<MCEngine::Scene>();
    entt::entity squareEntity =
        MCEngine::EntityFactory::CreateEntity(m_Scene->GetRegistry(), "Square", squareTransform, squareSprite);
    entt::entity cubeEntity =
        MCEngine::EntityFactory::CreateEntity(m_Scene->GetRegistry(), "Cube", cubeTransform, cubeMesh);

    m_Scene->GetRegistry().get<MCEngine::RelationshipComponent>(cubeEntity).AddChild(squareEntity);
    m_Scene->GetRegistry().get<MCEngine::RelationshipComponent>(squareEntity).SetParent(cubeEntity);
};

void MCEditor::EditorLayer::OnEvent(MCEngine::Event &event)
{
    ENGINE_PROFILE_FUNCTION();

    ImGuiLayer::OnEvent(event);

    MCEngine::EventDispatcher dispatcher(event);
    dispatcher.Dispatch<MCEngine::KeyEvent>([this](MCEngine::KeyEvent &e) {
        MCEngine::KeyCodeLibrary::GetInstance().SetKeyAction(e.GetKeyCode(), e.GetAction());
        return true;
    });

    m_Scene->OnEvent(event);
}

void MCEditor::EditorLayer::OnUpdate(float deltaTime)
{
    ENGINE_PROFILE_FUNCTION();

    m_Scene->Update(deltaTime);
}

void MCEditor::EditorLayer::OnRender()
{
    ENGINE_PROFILE_FUNCTION();

    m_Scene->Render();
}

void MCEditor::EditorLayer::Begin(float deltaTime)
{
    ENGINE_PROFILE_FUNCTION();

    ImGuiLayer::Begin(deltaTime);

    BeginDockSpace();

    RenderSceneHierarchy();

    ImGui::Begin("Event Info");
    ImGui::Text("Delta Time: %.3f ms/frame (%.1f FPS)", deltaTime * 1000.0f, 1.0f / deltaTime);
    ImGui::Text("Mouse Position: (%.1f, %.1f)", ImGui::GetIO().MousePos.x, ImGui::GetIO().MousePos.y);
    ImGui::Text("Mouse Buttons: Left(%d), Right(%d), Middle(%d)", ImGui::GetIO().MouseDown[0],
                ImGui::GetIO().MouseDown[1], ImGui::GetIO().MouseDown[2]);
    ImGui::End();

    EndDockSpace();
}

void MCEditor::EditorLayer::BeginDockSpace()
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

void MCEditor::EditorLayer::EndDockSpace()
{
    ENGINE_PROFILE_FUNCTION();

    ImGui::End();
}

void MCEditor::EditorLayer::RenderMenuBar()
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

void MCEditor::EditorLayer::RenderSceneHierarchy()
{
    ENGINE_PROFILE_FUNCTION();

    ImGui::Begin("Scene Hierarchy");

    auto view = m_Scene->GetRegistry().view<MCEngine::TagComponent, MCEngine::RelationshipComponent>();
    for (auto entity : view)
    {
        auto &rel = view.get<MCEngine::RelationshipComponent>(entity);
        if (rel.GetParent() == entt::null)
            DrawEntityNode(entity);
    }

    ImGui::End();
}

void MCEditor::EditorLayer::DrawEntityNode(entt::entity entity)
{
    auto &registry = m_Scene->GetRegistry();
    auto &tag = registry.get<MCEngine::TagComponent>(entity);

    ImGuiTreeNodeFlags node_flags = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_SpanAvailWidth;
    bool opened =
        ImGui::TreeNodeEx((void *)(uint64_t)(uint32_t)entity, node_flags, tag.GetTag().c_str(), (uint32_t)entity);

    if (opened)
    {
        if (auto *rel = registry.try_get<MCEngine::RelationshipComponent>(entity))
        {
            for (auto child : rel->GetChildren())
            {
                DrawEntityNode(child);
            }
        }
        ImGui::TreePop();
    }
}
