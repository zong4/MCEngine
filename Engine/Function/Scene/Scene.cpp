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

void MCEngine::Scene::Render(CameraComponent &camera) const
{
    ENGINE_PROFILE_FUNCTION();

    UniformBufferLibrary::GetInstance().UpdateUniformBuffer(
        "MainCamera",
        {{glm::value_ptr(camera.GetTransformComponent()->GetPosition()), sizeof(glm::vec3), 0},
         {glm::value_ptr(camera.GetViewMatrix()), sizeof(glm::mat4), sizeof(glm::vec4)},
         {glm::value_ptr(camera.GetProjectionMatrix()), sizeof(glm::mat4), sizeof(glm::vec4) + sizeof(glm::mat4)}});
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