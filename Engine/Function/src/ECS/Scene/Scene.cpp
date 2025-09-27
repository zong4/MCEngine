#include "Scene.hpp"

MCEngine::Scene::Scene()
{
    ENGINE_PROFILE_FUNCTION();

    m_Camera = m_Registry.create();
    auto &&transformComponent =
        m_Registry.emplace<TransformComponent>(m_Camera, TransformComponent(glm::vec3(0.0f, 0.0f, 0.0f)));
    auto &&cameraComponent =
        m_Registry.emplace<OrthoCameraComponent>(m_Camera, OrthoCameraComponent(glm::vec3(16.0f, 9.0f, 10.0f)));
    UpdateCamera(transformComponent.Position, transformComponent.Rotation);

    // Default light
    m_Light = m_Registry.create();
    m_Registry.emplace<TransformComponent>(m_Light, TransformComponent(glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.0f)));
    m_Registry.emplace<LightComponent>(m_Light, LightComponent(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), 1.0f));
}

void MCEngine::Scene::Update(float deltaTime)
{
    ENGINE_PROFILE_FUNCTION();

    auto &&cameraTransformComponent = m_Registry.get<TransformComponent>(m_Camera);

    // Move camera
    {
        if (KeyCodeLibrary::GetInstance().IsKeyDown(ENGINE_KEY_W))
        {
            UpdateCamera(cameraTransformComponent.Position + glm::vec3(0.0f, m_CameraMoveSpeed * deltaTime, 0.0f),
                         cameraTransformComponent.Rotation);
        }
        if (KeyCodeLibrary::GetInstance().IsKeyDown(ENGINE_KEY_S))
        {
            UpdateCamera(cameraTransformComponent.Position + glm::vec3(0.0f, -m_CameraMoveSpeed * deltaTime, 0.0f),
                         cameraTransformComponent.Rotation);
        }
        if (KeyCodeLibrary::GetInstance().IsKeyDown(ENGINE_KEY_A))
        {
            UpdateCamera(cameraTransformComponent.Position + glm::vec3(-m_CameraMoveSpeed * deltaTime, 0.0f, 0.0f),
                         cameraTransformComponent.Rotation);
        }
        if (KeyCodeLibrary::GetInstance().IsKeyDown(ENGINE_KEY_D))
        {
            UpdateCamera(cameraTransformComponent.Position + glm::vec3(m_CameraMoveSpeed * deltaTime, 0.0f, 0.0f),
                         cameraTransformComponent.Rotation);
        }
        if (KeyCodeLibrary::GetInstance().IsKeyDown(ENGINE_KEY_Q))
        {
            UpdateCamera(cameraTransformComponent.Position,
                         cameraTransformComponent.Rotation + glm::vec3(0.0f, 0.0f, m_CameraRotateSpeed * deltaTime));
        }
        if (KeyCodeLibrary::GetInstance().IsKeyDown(ENGINE_KEY_E))
        {
            UpdateCamera(cameraTransformComponent.Position,
                         cameraTransformComponent.Rotation + glm::vec3(0.0f, 0.0f, -m_CameraRotateSpeed * deltaTime));
        }
    }

    // Rotate camera
    {
        if (KeyCodeLibrary::GetInstance().IsKeyDown(ENGINE_KEY_I))
        {
            UpdateCamera(cameraTransformComponent.Position,
                         cameraTransformComponent.Rotation + glm::vec3(-m_CameraRotateSpeed * deltaTime, 0.0f, 0.0f));
        }
        if (KeyCodeLibrary::GetInstance().IsKeyDown(ENGINE_KEY_K))
        {
            UpdateCamera(cameraTransformComponent.Position,
                         cameraTransformComponent.Rotation + glm::vec3(m_CameraRotateSpeed * deltaTime, 0.0f, 0.0f));
        }
        if (KeyCodeLibrary::GetInstance().IsKeyDown(ENGINE_KEY_J))
        {
            UpdateCamera(cameraTransformComponent.Position,
                         cameraTransformComponent.Rotation + glm::vec3(0.0f, -m_CameraRotateSpeed * deltaTime, 0.0f));
        }
        if (KeyCodeLibrary::GetInstance().IsKeyDown(ENGINE_KEY_L))
        {
            UpdateCamera(cameraTransformComponent.Position,
                         cameraTransformComponent.Rotation + glm::vec3(0.0f, m_CameraRotateSpeed * deltaTime, 0.0f));
        }
        if (KeyCodeLibrary::GetInstance().IsKeyDown(ENGINE_KEY_U))
        {
            UpdateCamera(cameraTransformComponent.Position,
                         cameraTransformComponent.Rotation + glm::vec3(0.0f, 0.0f, m_CameraRotateSpeed * deltaTime));
        }
        if (KeyCodeLibrary::GetInstance().IsKeyDown(ENGINE_KEY_O))
        {
            UpdateCamera(cameraTransformComponent.Position,
                         cameraTransformComponent.Rotation + glm::vec3(0.0f, 0.0f, -m_CameraRotateSpeed * deltaTime));
        }
    }
}

void MCEngine::Scene::Render() const
{
    ENGINE_PROFILE_FUNCTION();

    auto &&cameraTransformComponent = m_Registry.get<TransformComponent>(m_Camera);
    auto &&cameraComponent = m_Registry.get<OrthoCameraComponent>(m_Camera);

    // Render 2D
    {
        auto &&shader = ShaderLibrary::GetInstance().GetShader("Texture");
        shader->Bind();

        shader->SetUniformMat4("u_View", cameraComponent.ViewMatrix);
        shader->SetUniformMat4("u_Projection", cameraComponent.ProjectionMatrix);

        auto &&spriteView = m_Registry.view<TransformComponent, SpriteRendererComponent>();
        for (auto entity : spriteView)
        {
            auto &&[transform, sprite] = spriteView.get<TransformComponent, SpriteRendererComponent>(entity);

            // Transform component
            shader->SetUniformMat4("u_Model", transform.GetTransformMatrix());

            // Sprite component
            shader->SetUniformVec4("u_Color", sprite.Color);
            shader->SetUniformInt("u_Texture", 0);
            sprite.TexturePtr->Bind(0);

            RendererAPI::GetInstance().DrawQuad(sprite.VAOPtr);
        }

        shader->Unbind();
    }

    // Render 3D
    {
        auto &&shader = ShaderLibrary::GetInstance().GetShader("BlinnPhong");
        shader->Bind();

        // Camera
        shader->SetUniformVec3("u_ViewPos", cameraTransformComponent.Position);
        shader->SetUniformMat4("u_View", cameraComponent.ViewMatrix);
        shader->SetUniformMat4("u_Projection", cameraComponent.ProjectionMatrix);

        // Light
        shader->SetUniformVec3("u_LightPos", m_Registry.get<TransformComponent>(m_Light).Position);
        shader->SetUniformVec4("u_LightColor", m_Registry.get<LightComponent>(m_Light).Color);

        auto meshView = m_Registry.view<TransformComponent, MeshRendererComponent>();
        for (auto entity : meshView)
        {
            auto &&[transform, mesh] = meshView.get<TransformComponent, MeshRendererComponent>(entity);

            // Transform component
            shader->SetUniformMat4("u_Model", transform.GetTransformMatrix());

            // Mesh component
            shader->SetUniformVec4("u_ObjectColor", mesh.Color);

            RendererAPI::GetInstance().DrawQuad(mesh.VAOPtr);
        }

        shader->Unbind();
    }
}

void MCEngine::Scene::UpdateCamera(glm::vec3 position, glm::vec3 rotation)
{
    auto &&cameraTransformComponent = m_Registry.get<TransformComponent>(m_Camera);
    auto &&cameraComponent = m_Registry.get<OrthoCameraComponent>(m_Camera);

    cameraTransformComponent.Position = position;
    cameraTransformComponent.Rotation = rotation;
    cameraComponent.UpdateViewMatrix(cameraTransformComponent.Position, cameraTransformComponent.Rotation);
    cameraComponent.UpdateProjectionMatrix();
}