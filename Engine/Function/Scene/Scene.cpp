#include "Scene.hpp"

#include <imgui.h>

MCEngine::Scene::Scene()
{
    ENGINE_PROFILE_FUNCTION();

    m_Camera2D = EntityFactory::CreateOrthoCamera(m_Registry, "MainCamera2D");
    m_Camera3D = EntityFactory::CreatePerspectiveCamera(m_Registry, "MainCamera3D");
    m_MainCamera = m_Camera3D;
}

MCEngine::Scene::~Scene() {}

void MCEngine::Scene::Update(float deltaTime)
{
    ENGINE_PROFILE_FUNCTION();

    // Switch camera
    {
        if (ImGui::IsKeyDown(ImGuiKey_1))
        {
            m_MainCamera = m_Camera2D;
            LOG_ENGINE_TRACE("Switched to 2D Camera");
        }
        if (ImGui::IsKeyDown(ImGuiKey_2))
        {
            m_MainCamera = m_Camera3D;
            LOG_ENGINE_TRACE("Switched to 3D Camera");
        }
    }

    m_Registry.get<CameraComponent>(m_MainCamera).Update(deltaTime);

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

void MCEngine::Scene::Render(CameraComponent *camera) const
{
    RenderAll(camera->GetViewMatrix(), camera->GetProjectionMatrix(), camera->GetTransformComponent()->GetPosition());
}

void MCEngine::Scene::Render(CameraComponent &camera) const
{
    RenderAll(camera.GetViewMatrix(), camera.GetProjectionMatrix(), camera.GetTransformComponent()->GetPosition());
}

void MCEngine::Scene::Render(const CameraComponent &camera) const
{
    RenderAll(camera.GetViewMatrix(), camera.GetProjectionMatrix(), camera.GetTransformComponent()->GetPosition());
}

void MCEngine::Scene::Resize(float width, float height)
{
    ENGINE_PROFILE_FUNCTION();

    auto view = m_Registry.view<CameraComponent>();
    for (auto entity : view)
    {
        auto &camera = view.get<CameraComponent>(entity);
        camera.Resize(width, height);
    }
}

void MCEngine::Scene::RenderAll(glm::mat4 viewMatrix, glm::mat4 projectionMatrix, glm::vec3 cameraPosition) const
{
    ENGINE_PROFILE_FUNCTION();

    UniformBufferLibrary::GetInstance().UpdateUniformBuffer(
        "MainCamera", {{glm::value_ptr(cameraPosition), sizeof(glm::vec3), 0},
                       {glm::value_ptr(viewMatrix), sizeof(glm::mat4), sizeof(glm::vec4)},
                       {glm::value_ptr(projectionMatrix), sizeof(glm::mat4), sizeof(glm::vec4) + sizeof(glm::mat4)}});

    // 2D
    {
        auto &&shader = ShaderLibrary::GetInstance().GetShader("Texture");
        shader->Bind();

        auto &&spriteView = m_Registry.view<TransformComponent, SpriteRendererComponent>();
        for (auto entity : spriteView)
        {
            auto &&[transform, sprite] = spriteView.get<TransformComponent, SpriteRendererComponent>(entity);

            shader->SetUniformMat4("u_Model", transform.GetTransformMatrix());
            shader->SetUniformVec4("u_Color", sprite.GetColor());
            shader->SetUniformInt("u_Texture", 0);
            sprite.GetTexturePtr()->Bind(0);

            sprite.GetVAOPtr()->Render();
        }

        shader->Unbind();
    }

    // 3D
    {
        auto &&shader = ShaderLibrary::GetInstance().GetShader("BlinnPhong");
        shader->Bind();

        // Light
        auto &&lightView = m_Registry.view<TransformComponent, LightComponent>();
        for (auto entity : lightView)
        {
            auto &&[transform, light] = lightView.get<TransformComponent, LightComponent>(entity);

            if (light.GetType() == LightType::Directional)
            {
                shader->SetUniformVec3("u_DirectionalLight.Position", glm::normalize(-transform.GetPosition()));
                shader->SetUniformVec3("u_DirectionalLight.Color", light.GetColor() * light.GetIntensity());
            }
            else if (light.GetType() == LightType::Point)
            {
                shader->SetUniformVec3("u_PointLight.Position", transform.GetPosition());
                shader->SetUniformVec3("u_PointLight.Color", light.GetColor() * light.GetIntensity());
                shader->SetUniformFloat("u_PointLight.Constant", light.GetConstant());
                shader->SetUniformFloat("u_PointLight.Linear", light.GetLinear());
                shader->SetUniformFloat("u_PointLight.Quadratic", light.GetQuadratic());
            }
            else if (light.GetType() == LightType::Spot)
            {
                shader->SetUniformVec3("u_SpotLight.Position", transform.GetPosition());
                shader->SetUniformVec3("u_SpotLight.Direction", -transform.GetUp());
                shader->SetUniformVec3("u_SpotLight.Color", light.GetColor() * light.GetIntensity());
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

    // Skybox
    {
        RendererCommand::DisableDepthTest();
        auto &&shader = ShaderLibrary::GetInstance().GetShader("Skybox");
        shader->Bind();

        auto skyboxView = m_Registry.view<SkyboxComponent>();
        for (auto entity : skyboxView)
        {
            auto &&skybox = skyboxView.get<SkyboxComponent>(entity);

            shader->SetUniformInt("u_Skybox", 0);
            skybox.GetTextureCubePtr()->Bind(0);

            VAOLibrary::GetInstance().GetVAO("Skybox")->Render();
        }

        shader->Unbind();
        RendererCommand::EnableDepthTest();
    }
}