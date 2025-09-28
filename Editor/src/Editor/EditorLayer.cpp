#include "EditorLayer.hpp"

#include <imgui.h>

MCEditor::EditorLayer::EditorLayer(std::shared_ptr<MCEngine::Window> windowPtr)
    : ImGuiLayer(windowPtr, std::string(PROJECT_ROOT) + "/Editor/configs/imgui.ini", "EditorLayer")
{
    ENGINE_PROFILE_FUNCTION();

    m_Scene = std::make_shared<MCEngine::Scene>();

    entt::entity squareEntity = MCEngine::EntityFactory::CreateBasicSquare(
        m_Scene->GetRegistry(), "Square", glm::vec3(0.0f), glm::vec3(0.0f), glm::vec3(3.0f));

    // 3D
    {
        entt::entity cubes = MCEngine::EntityFactory::CreateEmptyEntity(m_Scene->GetRegistry(), "Cubes");
        for (int i = 0; i < 5; i++)
        {
            for (int j = 0; j < 5; j++)
            {
                entt::entity cubeEntity = MCEngine::EntityFactory::CreateBasicCube(m_Scene->GetRegistry(), "Cube",
                                                                                   glm::vec3(i * 1.0f, 0.0f, j * 1.0f));
                m_Scene->GetRegistry().get<MCEngine::RelationshipComponent>(cubeEntity).SetParent(cubes);
                m_Scene->GetRegistry().get<MCEngine::RelationshipComponent>(cubes).AddChild(cubeEntity);
            }
        }
    }
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

    // m_Scene->Render2D();
    m_Scene->Render3D();
}

void MCEditor::EditorLayer::Begin(float deltaTime)
{
    ENGINE_PROFILE_FUNCTION();

    ImGuiLayer::Begin(deltaTime);

    BeginDockSpace();

    RenderSceneHierarchy();
    RenderInspector();

    // ImGui::Begin("Event Info");
    // ImGui::Text("Delta Time: %.3f ms/frame (%.1f FPS)", deltaTime * 1000.0f, 1.0f / deltaTime);
    // ImGui::Text("Mouse Position: (%.1f, %.1f)", ImGui::GetIO().MousePos.x, ImGui::GetIO().MousePos.y);
    // ImGui::Text("Mouse Buttons: Left(%d), Right(%d), Middle(%d)", ImGui::GetIO().MouseDown[0],
    //             ImGui::GetIO().MouseDown[1], ImGui::GetIO().MouseDown[2]);
    // ImGui::End();

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

    auto &&view = m_Scene->GetRegistry().view<MCEngine::TagComponent, MCEngine::RelationshipComponent>();
    for (auto entity : view)
    {
        auto &&rel = view.get<MCEngine::RelationshipComponent>(entity);
        if (rel.GetParent() == entt::null)
            DrawEntityNode(entity);
    }

    ImGui::End();
}

void MCEditor::EditorLayer::DrawEntityNode(entt::entity entity)
{
    auto &&view = m_Scene->GetRegistry().view<MCEngine::TagComponent, MCEngine::RelationshipComponent>();

    ImGuiTreeNodeFlags node_flags = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_SpanAvailWidth;
    bool opened = ImGui::TreeNodeEx((void *)(uint64_t)(uint32_t)entity, node_flags,
                                    view.get<MCEngine::TagComponent>(entity).GetTag().c_str(), (uint32_t)entity);

    if (ImGui::IsItemClicked())
        m_SelectedEntity = entity;

    if (opened)
    {
        for (auto child : view.get<MCEngine::RelationshipComponent>(entity).GetChildren())
        {
            DrawEntityNode(child);
        }
        ImGui::TreePop();
    }
}

// todo: add components
void MCEditor::EditorLayer::RenderInspector()
{
    ImGui::Begin("Inspector");

    if (m_SelectedEntity != entt::null)
    {
        auto &registry = m_Scene->GetRegistry();

        // TagComponent
        if (auto &&tag = registry.try_get<MCEngine::TagComponent>(m_SelectedEntity))
        {
            std::string header = "Tag Component##" + std::to_string(static_cast<uint32_t>(m_SelectedEntity));
            if (ImGui::CollapsingHeader(header.c_str(), ImGuiTreeNodeFlags_DefaultOpen))
            {
                char buffer[256];
                memset(buffer, 0, sizeof(buffer));
                strncpy(buffer, tag->GetTag().c_str(), sizeof(buffer));
                if (ImGui::InputText("Tag", buffer, sizeof(buffer)))
                    tag->SetTag(std::string(buffer));
            }
        }

        // TransformComponent
        if (auto &&transform = registry.try_get<MCEngine::TransformComponent>(m_SelectedEntity))
        {
            std::string header = "Transform Component##" + std::to_string(static_cast<uint32_t>(m_SelectedEntity));
            if (ImGui::CollapsingHeader(header.c_str(), ImGuiTreeNodeFlags_DefaultOpen))
            {
                ImGui::DragFloat3("Position", glm::value_ptr(transform->GetPosition()), 0.1f);
                ImGui::DragFloat3("Rotation", glm::value_ptr(transform->GetRotation()), 0.1f);
                ImGui::DragFloat3("Scale", glm::value_ptr(transform->GetScale()), 0.1f);
            }
        }

        // SpriteRendererComponent
        if (auto &&spriteRenderer = registry.try_get<MCEngine::SpriteRendererComponent>(m_SelectedEntity))
        {
            std::string header =
                "Sprite Renderer Component##" + std::to_string(static_cast<uint32_t>(m_SelectedEntity));
            if (ImGui::CollapsingHeader(header.c_str(), ImGuiTreeNodeFlags_DefaultOpen))
            {
                ImGui::ColorEdit4("Color", glm::value_ptr(spriteRenderer->GetColor()));
            }
        }

        // MeshRendererComponent
        if (auto &&meshRenderer = registry.try_get<MCEngine::MeshRendererComponent>(m_SelectedEntity))
        {
            std::string header = "Mesh Renderer Component##" + std::to_string(static_cast<uint32_t>(m_SelectedEntity));
            if (ImGui::CollapsingHeader(header.c_str(), ImGuiTreeNodeFlags_DefaultOpen))
            {
                ImGui::ColorEdit4("Color", glm::value_ptr(meshRenderer->GetColor()));
            }
        }

        // LightComponent
        if (auto &&light = registry.try_get<MCEngine::LightComponent>(m_SelectedEntity))
        {
            std::string header = "Light Component##" + std::to_string(static_cast<uint32_t>(m_SelectedEntity));
            if (ImGui::CollapsingHeader(header.c_str(), ImGuiTreeNodeFlags_DefaultOpen))
            {
                ImGui::ColorEdit4("Light Color", glm::value_ptr(light->GetColor()));
                ImGui::DragFloat("Intensity", &light->GetIntensity(), 0.1f, 0.0f, 100.0f);
            }
        }
    }

    ImGui::End();
}
