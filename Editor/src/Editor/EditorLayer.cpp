#include "EditorLayer.hpp"

#include <imgui.h>

MCEditor::EditorLayer::EditorLayer(std::shared_ptr<MCEngine::Window> windowPtr)
    : ImGuiLayer(windowPtr, std::string(PROJECT_ROOT) + "/Editor/configs/imgui.ini", "EditorLayer")
{
    ENGINE_PROFILE_FUNCTION();

    m_TransformPtr =
        new MCEngine::TransformComponent(glm::vec3(0.0f, 5.0f, 8.0f), glm::vec3(-30.0f, 0.0f, 0.0f), glm::vec3(1.0f));
    m_CameraPtr = new MCEngine::CameraComponent(
        m_TransformPtr, 45.0f, (float)windowPtr->GetProps().GetWidth() / (float)windowPtr->GetProps().GetHeight(), 0.1f,
        100.0f);
    m_ScenePtr = std::make_unique<MCEngine::Scene>();

    m_SceneFrameBufferPtr = std::make_unique<MCEngine::FrameBuffer>(windowPtr->GetProps().GetWidth(),
                                                                    windowPtr->GetProps().GetHeight(), 0x88F0);
    m_GameFrameBufferPtr = std::make_unique<MCEngine::FrameBuffer>(windowPtr->GetProps().GetWidth(),
                                                                   windowPtr->GetProps().GetHeight(), 0x88F0);

    // 2D
    {
        entt::entity squareEntity = MCEngine::EntityFactory::CreateSquare(
            m_ScenePtr->GetRegistry(), "Square", glm::vec3(0.0f), glm::vec3(0.0f), glm::vec3(5.0f), glm::vec4(1.0f),
            MCEngine::Texture2DLibrary::GetInstance().GetTexture("02BG"));
    }

    // 3D
    {
        entt::entity cubes = MCEngine::EntityFactory::CreateEmptyEntity(m_ScenePtr->GetRegistry(), "Cubes");
        for (int i = 0; i < 5; i++)
        {
            for (int j = 0; j < 5; j++)
            {
                entt::entity cubeEntity = MCEngine::EntityFactory::CreateCube(m_ScenePtr->GetRegistry(), "Cube",
                                                                              glm::vec3(i * 1.0f, 0.0f, j * 1.0f));
                m_ScenePtr->GetRegistry().get<MCEngine::RelationshipComponent>(cubeEntity).SetParent(cubes);
                m_ScenePtr->GetRegistry().get<MCEngine::RelationshipComponent>(cubes).AddChild(cubeEntity);
            }
        }

        // Default light
        {
            entt::entity light =
                MCEngine::EntityFactory::CreateDirectionalLight(m_ScenePtr->GetRegistry(), "DirectionalLight");
            MCEngine::EntityFactory::AddComponents(
                m_ScenePtr->GetRegistry(), light,
                MCEngine::MeshRendererComponent(
                    MCEngine::VAOLibrary::GetInstance().GetVAO("Cube"),
                    MCEngine::Material(glm::vec4(1.0f), glm::vec3(0.3f), glm::vec3(1.0f), glm::vec3(0.5f), 32.0f)));
        }
        {
            entt::entity light = MCEngine::EntityFactory::CreatePointLight(m_ScenePtr->GetRegistry(), "PointLight");
            MCEngine::EntityFactory::AddComponents(
                m_ScenePtr->GetRegistry(), light,
                MCEngine::MeshRendererComponent(
                    MCEngine::VAOLibrary::GetInstance().GetVAO("Cube"),
                    MCEngine::Material(glm::vec4(1.0f), glm::vec3(0.3f), glm::vec3(1.0f), glm::vec3(0.5f), 32.0f)));
        }
        {
            entt::entity light = MCEngine::EntityFactory::CreateSpotLight(m_ScenePtr->GetRegistry(), "SpotLight");
            MCEngine::EntityFactory::AddComponents(
                m_ScenePtr->GetRegistry(), light,
                MCEngine::MeshRendererComponent(
                    MCEngine::VAOLibrary::GetInstance().GetVAO("Cube"),
                    MCEngine::Material(glm::vec4(1.0f), glm::vec3(0.3f), glm::vec3(1.0f), glm::vec3(0.5f), 32.0f)));
        }

        // Skybox
        {
            entt::entity skybox = MCEngine::EntityFactory::CreateEmptyEntity(m_ScenePtr->GetRegistry(), "Skybox");
            MCEngine::EntityFactory::AddComponents(
                m_ScenePtr->GetRegistry(), skybox,
                MCEngine::SkyboxComponent(std::string(PROJECT_ROOT) + "/Engine/Assets/Images/skybox"));
        }
    }
};

MCEditor::EditorLayer::~EditorLayer()
{
    delete m_TransformPtr;
    delete m_CameraPtr;
}

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

    // Move Camera
    if (m_SceneFocused)
    {
        if (ImGui::IsKeyDown(ImGuiKey_W))
            m_TransformPtr->SetPosition(m_TransformPtr->GetPosition() +
                                        glm::vec3(0.0f, 1.0f, 0.0f) * m_CameraMoveSpeed * deltaTime);
        if (ImGui::IsKeyDown(ImGuiKey_S))
            m_TransformPtr->SetPosition(m_TransformPtr->GetPosition() -
                                        glm::vec3(0.0f, 1.0f, 0.0f) * m_CameraMoveSpeed * deltaTime);
        if (ImGui::IsKeyDown(ImGuiKey_A))
            m_TransformPtr->SetPosition(m_TransformPtr->GetPosition() -
                                        glm::vec3(1.0f, 0.0f, 0.0f) * m_CameraMoveSpeed * deltaTime);
        if (ImGui::IsKeyDown(ImGuiKey_D))
            m_TransformPtr->SetPosition(m_TransformPtr->GetPosition() +
                                        glm::vec3(1.0f, 0.0f, 0.0f) * m_CameraMoveSpeed * deltaTime);
        if (ImGui::IsKeyDown(ImGuiKey_Q))
            m_TransformPtr->SetPosition(m_TransformPtr->GetPosition() -
                                        glm::vec3(0.0f, 0.0f, 1.0f) * m_CameraMoveSpeed * deltaTime);
        if (ImGui::IsKeyDown(ImGuiKey_E))
            m_TransformPtr->SetPosition(m_TransformPtr->GetPosition() +
                                        glm::vec3(0.0f, 0.0f, 1.0f) * m_CameraMoveSpeed * deltaTime);

        m_CameraPtr->Update(deltaTime);
    }

    if (m_GameFocused)
    {
        m_ScenePtr->Update(deltaTime);
    }
}

void MCEditor::EditorLayer::OnRender()
{
    ENGINE_PROFILE_FUNCTION();

    m_SceneFrameBufferPtr->Bind();
    MCEngine::RendererCommand::Clear();
    m_ScenePtr->Render(m_CameraPtr);
    m_SceneFrameBufferPtr->Unbind();

    m_GameFrameBufferPtr->Bind();
    MCEngine::RendererCommand::Clear();
    m_ScenePtr->Render(m_ScenePtr->GetRegistry().get<MCEngine::CameraComponent>(m_ScenePtr->GetMainCamera()));
    m_GameFrameBufferPtr->Unbind();
}

void MCEditor::EditorLayer::Begin(float deltaTime)
{
    ENGINE_PROFILE_FUNCTION();

    ImGuiLayer::Begin(deltaTime);

    BeginDockSpace();

    RenderHierarchy();
    RenderInspector();
    RenderScene();
    RenderGame();

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

void MCEditor::EditorLayer::RenderHierarchy()
{
    ENGINE_PROFILE_FUNCTION();

    ImGui::Begin("Hierarchy");

    auto &&view = m_ScenePtr->GetRegistry().view<MCEngine::TagComponent, MCEngine::RelationshipComponent>();
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
    auto &&view = m_ScenePtr->GetRegistry().view<MCEngine::TagComponent, MCEngine::RelationshipComponent>();

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
        auto &registry = m_ScenePtr->GetRegistry();

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
                ImGui::ColorEdit4("Color", glm::value_ptr(meshRenderer->GetMaterial().GetObjectColor()));
                ImGui::DragFloat3("Ambient", glm::value_ptr(meshRenderer->GetMaterial().GetAmbientStrength()), 0.1f,
                                  0.0f, 1.0f);
                ImGui::DragFloat3("Diffuse", glm::value_ptr(meshRenderer->GetMaterial().GetDiffuseStrength()), 0.1f,
                                  0.0f, 1.0f);
                ImGui::DragFloat3("Specular", glm::value_ptr(meshRenderer->GetMaterial().GetSpecularStrength()), 0.1f,
                                  0.0f, 1.0f);
                ImGui::DragFloat("Shininess", &meshRenderer->GetMaterial().GetShininess(), 1.0f, 1.0f, 256.0f);
            }
        }

        // LightComponent
        if (auto &&light = registry.try_get<MCEngine::LightComponent>(m_SelectedEntity))
        {
            std::string header = "Light Component##" + std::to_string(static_cast<uint32_t>(m_SelectedEntity));
            if (ImGui::CollapsingHeader(header.c_str(), ImGuiTreeNodeFlags_DefaultOpen))
            {
                ImGui::ColorEdit3("Light Color", glm::value_ptr(light->GetColor()));
                ImGui::DragFloat("Intensity", &light->GetIntensity(), 1.0f, 0.0f, 100.0f);
            }
        }
    }

    ImGui::End();
}

void MCEditor::EditorLayer::RenderScene()
{
    ImGui::Begin("Scene");

    m_SceneFocused = ImGui::IsWindowFocused();

    ImVec2 viewportSize = ImGui::GetContentRegionAvail();
    if ((int)viewportSize.x != m_SceneFrameBufferPtr->GetWidth() ||
        (int)viewportSize.y != m_SceneFrameBufferPtr->GetHeight())
    {
        m_SceneFrameBufferPtr->Resize((int)viewportSize.x, (int)viewportSize.y);
        m_CameraPtr->Resize(viewportSize.x, viewportSize.y);
    }

    ImGui::Image((ImTextureID)(intptr_t)m_SceneFrameBufferPtr->GetTexturePtr()->GetRendererID(), viewportSize,
                 ImVec2(0, 1), ImVec2(1, 0));

    ImGui::End();
}

void MCEditor::EditorLayer::RenderGame()
{
    ImGui::Begin("Game");

    m_GameFocused = ImGui::IsWindowFocused();

    ImVec2 viewportSize = ImGui::GetContentRegionAvail();
    if ((int)viewportSize.x != m_GameFrameBufferPtr->GetWidth() ||
        (int)viewportSize.y != m_GameFrameBufferPtr->GetHeight())
    {
        m_GameFrameBufferPtr->Resize((int)viewportSize.x, (int)viewportSize.y);
        m_ScenePtr->Resize(viewportSize.x, viewportSize.y);
    }

    ImGui::Image((ImTextureID)(intptr_t)m_GameFrameBufferPtr->GetTexturePtr()->GetRendererID(), viewportSize,
                 ImVec2(0, 1), ImVec2(1, 0));

    ImGui::End();
}