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

    // Update all cameras
    auto &&view = m_Registry.view<CameraComponent>();
    for (auto &&entity : view)
    {
        auto &&camera = view.get<CameraComponent>(entity);
        camera.Update(deltaTime);
    }

    // Update all transforms
    {
        auto &&view = m_Registry.view<TransformComponent>();
        for (auto &&entity : view)
        {
            auto &&transform = view.get<TransformComponent>(entity);
            transform.Update(deltaTime);
        }
    }
}

void MCEngine::Scene::RenderShadowMap() const
{
    ENGINE_PROFILE_FUNCTION();

    m_ShadowMapPtr->Bind();
    RendererCommand::ClearDepthBuffer();

    RenderShadowMapReally();

    m_ShadowMapPtr->Unbind();
}

void MCEngine::Scene::Render(CameraComponent &camera) const
{
    ENGINE_PROFILE_FUNCTION();

    // todo: uniform buffer automatic calulation
    UniformBufferLibrary::GetInstance().UpdateUniformBuffer(
        "UniformBuffer0", {
                              {glm::value_ptr(camera.GetViewMatrix()), sizeof(glm::mat4), 0},
                              {glm::value_ptr(camera.GetProjectionMatrix()), sizeof(glm::mat4), sizeof(glm::mat4)},
                              {glm::value_ptr(camera.GetTransformComponent()->GetPosition()), sizeof(glm::vec3),
                               sizeof(glm::mat4) + sizeof(glm::mat4)},
                          });

    // 2D
    {
        auto &&shader = MCEngine::ShaderLibrary::GetInstance().GetShader("Texture");
        shader->Bind();

        auto &&spriteView = m_Registry.view<MCEngine::TransformComponent, MCEngine::SpriteRendererComponent>();
        for (auto &&entity : spriteView)
        {
            auto &&[transform, sprite] =
                spriteView.get<MCEngine::TransformComponent, MCEngine::SpriteRendererComponent>(entity);

            shader->SetUniformMat4("u_Model", transform.GetTransformMatrix());
            shader->SetUniformVec4("u_Color", sprite.GetColor());
            shader->SetUniformInt("u_Texture", 0);
            sprite.GetTexturePtr()->Bind(0);

            sprite.GetVAOPtr()->Render();
        }

        shader->Unbind();
    }

    RenderReally(camera);
}

void MCEngine::Scene::Resize(float width, float height)
{
    ENGINE_PROFILE_FUNCTION();

    auto &&view = m_Registry.view<CameraComponent>();
    for (auto &&entity : view)
    {
        auto &&camera = view.get<CameraComponent>(entity);
        camera.Resize(width, height);
    }
}