#include "EditorLayer.hpp"

#include <imgui.h>

MCEditor::EditorLayer::EditorLayer(const std::shared_ptr<MCEngine::Window> &windowPtr)
    : ImGuiLayer(windowPtr, std::string(PROJECT_ROOT) + "/Editor/Configs/imgui.ini", "EditorLayer")
{
    ENGINE_PROFILE_FUNCTION();

    m_ScenePtr = std::make_unique<MCEditor::FullScene>();

    InitCamera(windowPtr);
    InitScenePanel();
    InitGamePanel();
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

    if (m_SceneFocused)
    {
        m_CameraPtr->GetComponent<MCEngine::TransformComponent>().UpdateTransformMatrix();
        m_CameraPtr->GetComponent<MCEngine::TransformComponent>().UpdateViewMatrix();
        m_CameraPtr->OnUpdate(deltaTime);
    }

    m_ScenePtr->Update(deltaTime);
}

void MCEditor::EditorLayer::OnRender()
{
    ENGINE_PROFILE_FUNCTION();

    m_ScenePtr->RenderShadowMap();

    m_SceneMultisampleFBOPtr->Bind();
    MCEngine::RendererCommand::Clear();
    m_ScenePtr->Render(m_CameraPtr->GetEntity());
    m_SceneMultisampleFBOPtr->Blit(m_SceneFBOPtr->GetRendererID());
    m_SceneMultisampleFBOPtr->Unbind();

    m_GameMultisampleFBOPtr->Bind();
    MCEngine::RendererCommand::Clear();
    m_ScenePtr->Render(m_ScenePtr->GetMainCamera());
    m_GameMultisampleFBOPtr->Blit(m_GameFBOPtr->GetRendererID());
    m_GameMultisampleFBOPtr->Unbind();
}

void MCEditor::EditorLayer::InitCamera(const std::shared_ptr<MCEngine::Window> &windowPtr)
{
    ENGINE_PROFILE_FUNCTION();

    MCEngine::Entity cameraEntity(m_Registry.create(), &m_Registry);
    cameraEntity.AddComponent<MCEngine::TransformComponent>(glm::vec3(0.0f, 0.0f, 5.0f), glm::vec3(0.0f),
                                                            glm::vec3(1.0f));
    cameraEntity.AddComponent<MCEngine::CameraComponent>(45.0f, 16.0 / 9.0, 0.1f, 100.0f);
    cameraEntity.AddComponent<MCEngine::NativeScriptComponent>();

    auto &&nsc = cameraEntity.GetComponent<MCEngine::NativeScriptComponent>();
    nsc.Bind<CameraController>();
    nsc.InstantiateScript();
    nsc.Instance->SetEntity(cameraEntity);
    nsc.Instance->OnCreate();
    nsc.Instance->OnStart();
    m_CameraPtr = std::dynamic_pointer_cast<CameraController>(nsc.Instance);
}

void MCEditor::EditorLayer::InitScenePanel()
{
    ENGINE_PROFILE_FUNCTION();

    m_SceneFBOPtr = std::make_unique<MCEngine::FrameBuffer>(MCEngine::FrameBufferType::Color, 1280, 720);
    m_SceneMultisampleFBOPtr =
        std::make_unique<MCEngine::FrameBuffer>(MCEngine::FrameBufferType::MultiSample, 1280, 720, 4);
}

void MCEditor::EditorLayer::InitGamePanel()
{
    ENGINE_PROFILE_FUNCTION();

    m_GameFBOPtr = std::make_unique<MCEngine::FrameBuffer>(MCEngine::FrameBufferType::Color, 1280, 720);
    m_GameMultisampleFBOPtr =
        std::make_unique<MCEngine::FrameBuffer>(MCEngine::FrameBufferType::MultiSample, 1280, 720, 4);
}

void MCEditor::EditorLayer::Begin()
{
    ENGINE_PROFILE_FUNCTION();

    ImGuiLayer::Begin();

    BeginDockSpace();

    RenderHierarchyPanel();
    RenderInspectorPanel();
    RenderScenePanel();
    RenderGamePanel();
    RenderFileBrowserPanel();

    EndDockSpace();
}

void MCEditor::EditorLayer::BeginDockSpace() const
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

void MCEditor::EditorLayer::EndDockSpace() const
{
    ENGINE_PROFILE_FUNCTION();

    ImGui::End();
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

void MCEditor::EditorLayer::RenderHierarchyPanel()
{
    ENGINE_PROFILE_FUNCTION();

    ImGui::Begin("Hierarchy");

    auto &&view = m_ScenePtr->GetRegistry().view<MCEngine::TagComponent, MCEngine::RelationshipComponent>();
    for (auto &&entity : view)
    {
        auto &&rel = view.get<MCEngine::RelationshipComponent>(entity);
        if (!rel.GetParent())
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
        for (auto &&child : view.get<MCEngine::RelationshipComponent>(entity).GetChildren())
            DrawEntityNode(child);
        ImGui::TreePop();
    }
}

// todo: add components
void MCEditor::EditorLayer::RenderInspectorPanel()
{
    ImGui::Begin("Inspector");

    if (m_SelectedEntity != entt::null)
    {
        auto &&registry = m_ScenePtr->GetRegistry();

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
                ImGui::ColorEdit4("Color", glm::value_ptr(meshRenderer->GetMaterial().GetColor()));
                ImGui::DragFloat("Ambient", &meshRenderer->GetMaterial().GetAmbientStrength(), 0.1f, 0.0f, 1.0f);
                ImGui::DragFloat("Diffuse", &meshRenderer->GetMaterial().GetDiffuseStrength(), 0.1f, 0.0f, 1.0f);
                ImGui::DragFloat("Specular", &meshRenderer->GetMaterial().GetSpecularStrength(), 0.1f, 0.0f, 1.0f);
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

void MCEditor::EditorLayer::RenderScenePanel()
{
    ImGui::Begin("Scene");

    m_SceneFocused = ImGui::IsWindowFocused();
    ImVec2 viewportSize = ImGui::GetContentRegionAvail();
    if ((int)viewportSize.x != m_SceneFBOPtr->GetWidth() || (int)viewportSize.y != m_SceneFBOPtr->GetHeight())
    {
        m_CameraPtr->GetComponent<MCEngine::CameraComponent>().Resize(viewportSize.x, viewportSize.y);

        m_SceneFBOPtr->Resize((int)viewportSize.x, (int)viewportSize.y);
        m_SceneMultisampleFBOPtr->Resize((int)viewportSize.x, (int)viewportSize.y);
        LOG_EDITOR_INFO("Resize Scene Framebuffer to width: " + std::to_string((int)viewportSize.x) +
                        " height: " + std::to_string((int)viewportSize.y));
    }
    ImGui::Image((ImTextureID)(intptr_t)m_SceneFBOPtr->GetTexturePtr()->GetRendererID(), viewportSize, ImVec2(0, 1),
                 ImVec2(1, 0));

    ImGui::End();
}

void MCEditor::EditorLayer::RenderGamePanel()
{
    ImGui::Begin("Game");

    m_GameFocused = ImGui::IsWindowFocused();
    ImVec2 viewportSize = ImGui::GetContentRegionAvail();
    if ((int)viewportSize.x != m_GameFBOPtr->GetWidth() || (int)viewportSize.y != m_GameFBOPtr->GetHeight())
    {
        m_ScenePtr->Resize(viewportSize.x, viewportSize.y);

        m_GameFBOPtr->Resize((int)viewportSize.x, (int)viewportSize.y);
        m_GameMultisampleFBOPtr->Resize((int)viewportSize.x, (int)viewportSize.y);
        LOG_EDITOR_INFO("Resize Game Framebuffer to width: " + std::to_string((int)viewportSize.x) +
                        " height: " + std::to_string((int)viewportSize.y));
    }
    ImGui::Image((ImTextureID)(intptr_t)m_GameFBOPtr->GetTexturePtr()->GetRendererID(), viewportSize, ImVec2(0, 1),
                 ImVec2(1, 0));

    ImGui::End();
}

void MCEditor::EditorLayer::RenderFileBrowserPanel()
{
    ImGui::Begin("File Browser");

    RenderFileBrowser(std::string(PROJECT_ROOT) + "Editor/Assets");

    ImGui::End();
}

void MCEditor::EditorLayer::RenderFileBrowser(const std::filesystem::path &directory)
{
    for (auto &&entry : std::filesystem::directory_iterator(directory))
    {
        if (entry.is_directory())
        {
            if (ImGui::TreeNode(entry.path().filename().string().c_str()))
            {
                RenderFileBrowser(entry.path());
                ImGui::TreePop();
            }
        }
        else
        {
            ImGui::BulletText("%s", entry.path().filename().string().c_str());
        }
    }
}