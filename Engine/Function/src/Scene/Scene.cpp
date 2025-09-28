#include "Scene.hpp"

MCEngine::Scene::Scene()
{
    ENGINE_PROFILE_FUNCTION();

    m_Camera2D = EntityFactory::CreateBasicOrthoCamera(m_Registry, "MainCamera2D", glm::vec3(0.0f), glm::vec3(0.0f),
                                                       glm::vec3(16.0f, 9.0f, 10.0f));
    m_Camera3D =
        EntityFactory::CreateBasicPerspectiveCamera(m_Registry, "MainCamera3D", glm::vec3(0.0f, 5.0f, 8.0f),
                                                    glm::vec3(-30.0f, 0.0f, 0.0f), 45.0f, 16.0f / 9.0f, 0.1f, 100.0f);
    m_Camera = m_Camera3D;

    // Default light
    m_Light = EntityFactory::CreateBasicPointLight(m_Registry, "MainLight");
    EntityFactory::AddComponents(m_Registry, m_Light,
                                 MeshRendererComponent(MCEngine::VAOLibrary::GetInstance().GetVAO("IdentityCube"),
                                                       m_Registry.get<LightComponent>(m_Light).GetColor()));
}

MCEngine::Scene::~Scene() {}

void MCEngine::Scene::Update(float deltaTime)
{
    ENGINE_PROFILE_FUNCTION();

    // Switch camera
    {
        if (KeyCodeLibrary::GetInstance().IsKeyDown(ENGINE_KEY_1))
        {
            m_Camera = m_Camera2D;
            LOG_ENGINE_INFO("Switched to 2D Camera");
        }
        if (KeyCodeLibrary::GetInstance().IsKeyDown(ENGINE_KEY_2))
        {
            m_Camera = m_Camera3D;
            LOG_ENGINE_INFO("Switched to 3D Camera");
        }
    }

    // Move Camera
    {
        auto &cameraTransform = m_Registry.get<TransformComponent>(m_Camera);
        if (KeyCodeLibrary::GetInstance().IsKeyDown(ENGINE_KEY_W))
            cameraTransform.SetPosition(cameraTransform.GetPosition() +
                                        glm::vec3(0.0f, 1.0f, 0.0f) * m_CameraMoveSpeed * deltaTime);
        if (KeyCodeLibrary::GetInstance().IsKeyDown(ENGINE_KEY_S))
            cameraTransform.SetPosition(cameraTransform.GetPosition() -
                                        glm::vec3(0.0f, 1.0f, 0.0f) * m_CameraMoveSpeed * deltaTime);
        if (KeyCodeLibrary::GetInstance().IsKeyDown(ENGINE_KEY_A))
            cameraTransform.SetPosition(cameraTransform.GetPosition() -
                                        glm::vec3(1.0f, 0.0f, 0.0f) * m_CameraMoveSpeed * deltaTime);
        if (KeyCodeLibrary::GetInstance().IsKeyDown(ENGINE_KEY_D))
            cameraTransform.SetPosition(cameraTransform.GetPosition() +
                                        glm::vec3(1.0f, 0.0f, 0.0f) * m_CameraMoveSpeed * deltaTime);
        if (KeyCodeLibrary::GetInstance().IsKeyDown(ENGINE_KEY_Q))
            cameraTransform.SetPosition(cameraTransform.GetPosition() -
                                        glm::vec3(0.0f, 0.0f, 1.0f) * m_CameraMoveSpeed * deltaTime);
        if (KeyCodeLibrary::GetInstance().IsKeyDown(ENGINE_KEY_E))
            cameraTransform.SetPosition(cameraTransform.GetPosition() +
                                        glm::vec3(0.0f, 0.0f, 1.0f) * m_CameraMoveSpeed * deltaTime);
    }

    m_Registry.get<CameraComponent>(m_Camera).Update(deltaTime);

    // Update all components
    {
        auto view = m_Registry.view<TransformComponent>();
        for (auto entity : view)
        {
            auto &transform = view.get<TransformComponent>(entity);
            transform.Update(deltaTime);
        }
    }
}

void MCEngine::Scene::Render2D() const
{
    ENGINE_PROFILE_FUNCTION();

    auto &&shader = ShaderLibrary::GetInstance().GetShader("Texture");
    shader->Bind();

    shader->SetUniformMat4("u_View", m_Registry.get<CameraComponent>(m_Camera).GetViewMatrix());
    shader->SetUniformMat4("u_Projection", m_Registry.get<CameraComponent>(m_Camera).GetProjectionMatrix());

    auto &&spriteView = m_Registry.view<TransformComponent, SpriteRendererComponent>();
    for (auto entity : spriteView)
    {
        auto &&[transform, sprite] = spriteView.get<TransformComponent, SpriteRendererComponent>(entity);

        // Transform component
        shader->SetUniformMat4("u_Model", transform.GetTransformMatrix());

        // Sprite component
        shader->SetUniformVec4("u_Color", sprite.GetColor());
        shader->SetUniformInt("u_Texture", 0);
        sprite.GetTexturePtr()->Bind(0);

        sprite.GetVAOPtr()->Render();
    }

    shader->Unbind();
}

void MCEngine::Scene::Render3D() const
{
    auto &&shader = ShaderLibrary::GetInstance().GetShader("BlinnPhong");
    shader->Bind();

    // Camera
    shader->SetUniformVec3("u_ViewPos", m_Registry.get<TransformComponent>(m_Camera).GetPosition());
    shader->SetUniformMat4("u_View", m_Registry.get<CameraComponent>(m_Camera).GetViewMatrix());
    shader->SetUniformMat4("u_Projection", m_Registry.get<CameraComponent>(m_Camera).GetProjectionMatrix());

    // Light
    shader->SetUniformVec3("u_LightPos", m_Registry.get<TransformComponent>(m_Light).GetPosition());
    shader->SetUniformVec4("u_LightColor", m_Registry.get<LightComponent>(m_Light).GetColor() *
                                               m_Registry.get<LightComponent>(m_Light).GetIntensity());

    // Shader
    shader->SetUniformFloat("u_AmbientStrength", 0.3f);
    shader->SetUniformFloat("u_DiffuseStrength", 1.0f);
    shader->SetUniformFloat("u_SpecularStrength", 1.0f);
    shader->SetUniformInt("u_Shininess", 32);

    auto meshView = m_Registry.view<TransformComponent, MeshRendererComponent>();
    for (auto entity : meshView)
    {
        auto &&[transform, mesh] = meshView.get<TransformComponent, MeshRendererComponent>(entity);

        // Transform component
        shader->SetUniformMat4("u_Model", transform.GetTransformMatrix());

        // Mesh component
        shader->SetUniformVec4("u_ObjectColor", mesh.GetColor());

        mesh.GetVAOPtr()->Render();
    }

    shader->Unbind();
}