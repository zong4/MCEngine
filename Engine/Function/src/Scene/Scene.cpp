#include "Scene.hpp"

MCEngine::Scene::Scene()
{
    ENGINE_PROFILE_FUNCTION();

    m_Camera2D = EntityFactory::CreateOrthoCamera(m_Registry, "MainCamera2D");
    m_Camera3D = EntityFactory::CreatePerspectiveCamera(m_Registry, "MainCamera3D");
    m_Camera = m_Camera3D;
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
    auto &&lightView = m_Registry.view<TransformComponent, LightComponent>();
    for (auto entity : lightView)
    {
        auto &&[transform, light] = lightView.get<TransformComponent, LightComponent>(entity);

        if (light.GetType() == LightType::Directional)
        {
            shader->SetUniformVec3("u_DirectionalLight.Position", glm::normalize(-transform.GetPosition()));
            shader->SetUniformVec3("u_DirectionalLight.Color", light.GetColor());
        }
        else if (light.GetType() == LightType::Point)
        {
            shader->SetUniformVec3("u_PointLight.Position", transform.GetPosition());
            shader->SetUniformVec3("u_PointLight.Color", light.GetColor());
            shader->SetUniformFloat("u_PointLight.Constant", light.GetConstant());
            shader->SetUniformFloat("u_PointLight.Linear", light.GetLinear());
            shader->SetUniformFloat("u_PointLight.Quadratic", light.GetQuadratic());
        }
        else if (light.GetType() == LightType::Spot)
        {
            shader->SetUniformVec3("u_SpotLight.Position", transform.GetPosition());
            shader->SetUniformVec3("u_SpotLight.Direction", -transform.GetUp());
            shader->SetUniformVec3("u_SpotLight.Color", light.GetColor());
            shader->SetUniformFloat("u_SpotLight.Constant", light.GetConstant());
            shader->SetUniformFloat("u_SpotLight.Linear", light.GetLinear());
            shader->SetUniformFloat("u_SpotLight.Quadratic", light.GetQuadratic());
            shader->SetUniformFloat("u_SpotLight.CutOff", glm::cos(glm::radians(light.GetCutOff())));
            shader->SetUniformFloat("u_SpotLight.OuterCutOff", glm::cos(glm::radians(light.GetOuterCutOff())));
        }
    }

    auto meshView = m_Registry.view<TransformComponent, MeshRendererComponent>();
    for (auto entity : meshView)
    {
        auto &&[transform, mesh] = meshView.get<TransformComponent, MeshRendererComponent>(entity);

        shader->SetUniformMat4("u_Model", transform.GetTransformMatrix());
        shader->SetUniformMaterial("u_Material", mesh.GetMaterial());

        mesh.GetVAOPtr()->Render();
    }

    shader->Unbind();
}