#include "Scene.hpp"

MCEngine::Scene::Scene()
{
    ENGINE_PROFILE_FUNCTION();

    m_Camera2D = EntityFactory::CreateBasicOrthoCamera(m_Registry, "MainCamera2D", glm::vec3(0.0f), glm::vec3(0.0f),
                                                       glm::vec3(16.0f, 9.0f, 10.0f));
    m_Camera3D = EntityFactory::CreateBasicPerspectiveCamera(m_Registry, "MainCamera3D", glm::vec3(0.0f, 0.0f, 5.0f),
                                                             glm::vec3(0.0f), 45.0f, 16.0f / 9.0f, 0.1f, 100.0f);
    m_Camera = m_Camera2D;
    m_CameraComponent = &m_Registry.get<OrthoCameraComponent>(m_Camera);

    // Default light
    m_Light = EntityFactory::CreateEmptyEntity(m_Registry, "MainLight");
    EntityFactory::AddComponents(m_Registry, m_Light, LightComponent(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), 1.0f));
}

MCEngine::Scene::~Scene()
{
    ENGINE_PROFILE_FUNCTION();

    m_Registry.clear();
}

void MCEngine::Scene::Update(float deltaTime)
{
    ENGINE_PROFILE_FUNCTION();

    // Switch camera
    {
        if (KeyCodeLibrary::GetInstance().IsKeyDown(ENGINE_KEY_1))
        {
            m_Camera = m_Camera2D;
            m_CameraComponent = &m_Registry.get<OrthoCameraComponent>(m_Camera);
            LOG_ENGINE_INFO("Switched to 2D Camera");
        }
        if (KeyCodeLibrary::GetInstance().IsKeyDown(ENGINE_KEY_2))
        {
            m_Camera = m_Camera3D;
            m_CameraComponent = &m_Registry.get<PerspectiveCameraComponent>(m_Camera);
            LOG_ENGINE_INFO("Switched to 3D Camera");
        }
    }

    // Move camera
    {
        if (KeyCodeLibrary::GetInstance().IsKeyDown(ENGINE_KEY_W))
        {
            m_Registry.get<TransformComponent>(m_Camera).SetPosition(
                m_Registry.get<TransformComponent>(m_Camera).GetPosition() +
                glm::vec3(0.0f, m_CameraMoveSpeed * deltaTime, 0.0f));
        }
        if (KeyCodeLibrary::GetInstance().IsKeyDown(ENGINE_KEY_S))
        {
            m_Registry.get<TransformComponent>(m_Camera).SetPosition(
                m_Registry.get<TransformComponent>(m_Camera).GetPosition() +
                glm::vec3(0.0f, -m_CameraMoveSpeed * deltaTime, 0.0f));
        }
    }

    m_CameraComponent->Update(deltaTime);

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

void MCEngine::Scene::Render() const
{
    ENGINE_PROFILE_FUNCTION();

    // Render 2D
    {
        auto &&shader = ShaderLibrary::GetInstance().GetShader("Texture");
        shader->Bind();

        shader->SetUniformMat4("u_View", m_CameraComponent->GetViewMatrix());
        shader->SetUniformMat4("u_Projection", m_CameraComponent->GetProjectionMatrix());

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

    // Render 3D
    {
        auto &&shader = ShaderLibrary::GetInstance().GetShader("BlinnPhong");
        shader->Bind();

        // Camera
        shader->SetUniformVec3("u_ViewPos", m_Registry.get<TransformComponent>(m_Camera).GetPosition());
        shader->SetUniformMat4("u_View", m_CameraComponent->GetViewMatrix());
        shader->SetUniformMat4("u_Projection", m_CameraComponent->GetProjectionMatrix());

        // Light
        shader->SetUniformVec3("u_LightPos", m_Registry.get<TransformComponent>(m_Light).GetPosition());
        shader->SetUniformVec4("u_LightColor", m_Registry.get<LightComponent>(m_Light).GetColor());

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
}