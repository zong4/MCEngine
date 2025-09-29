#pragma once

#include "ECS/Component/Basic/BasicComponent.hpp"
#include "ECS/Component/Camera/CameraComponent.hpp"
#include "ECS/Component/Light/LightComponent.hpp"
#include "ECS/Component/Renderer/RendererComponent.hpp"

namespace MCEngine
{

class EntityFactory
{
public:
    static entt::entity CreateEmptyEntity(entt::registry &registry, const std::string &name,
                                          const glm::vec3 &position = glm::vec3(0.0f),
                                          const glm::vec3 &rotation = glm::vec3(0.0f),
                                          const glm::vec3 &scale = glm::vec3(1.0f));
    static entt::entity CreateEmptyEntity(entt::registry &registry, const std::string &name,
                                          const TransformComponent &transform);

    static entt::entity CreateSquare(
        entt::registry &registry, const std::string &name, const glm::vec3 &position = glm::vec3(0.0f),
        const glm::vec3 &rotation = glm::vec3(0.0f), const glm::vec3 &scale = glm::vec3(1.0f),
        const glm::vec4 &color = glm::vec4(1.0f),
        std::shared_ptr<Texture2D> texturePtr = Texture2DLibrary::GetInstance().GetTexture("White"));
    static entt::entity CreateCube(entt::registry &registry, const std::string &name,
                                   const glm::vec3 &position = glm::vec3(0.0f),
                                   const glm::vec3 &rotation = glm::vec3(0.0f),
                                   const glm::vec3 &scale = glm::vec3(1.0f),
                                   const Material &material = Material(glm::vec4(1.0f), 0.3f, 1.0f, 0.5f, 32.0f));

    static entt::entity CreateOrthoCamera(entt::registry &registry, const std::string &name,
                                          const glm::vec3 &position = glm::vec3(0.0f),
                                          const glm::vec3 &rotation = glm::vec3(0.0f),
                                          const glm::vec3 &size = glm::vec3(16.0f, 9.0f, 10.0f));
    static entt::entity CreatePerspectiveCamera(entt::registry &registry, const std::string &name,
                                                const glm::vec3 &position = glm::vec3(0.0f, 5.0f, 8.0f),
                                                const glm::vec3 &rotation = glm::vec3(-30.0f, 0.0f, 0.0f),
                                                float fov = 45.0f, float aspectRatio = 16.0f / 9.0f,
                                                float nearClip = 0.1f, float farClip = 100.0f);

    static entt::entity CreateDirectionalLight(entt::registry &registry, const std::string &name,
                                               const glm::vec3 &position = glm::vec3(3.0f, 3.0f, 3.0f),
                                               const glm::vec3 &color = glm::vec3(1.0f, 0.0f, 0.0f),
                                               float intensity = 1.0f);
    static entt::entity CreatePointLight(entt::registry &registry, const std::string &name,
                                         const glm::vec3 &position = glm::vec3(3.0f, 3.0f, 0.0f),
                                         const glm::vec3 &color = glm::vec3(1.0f), float intensity = 1.0f,
                                         float constant = 1.0f, float linear = 0.09f, float quadratic = 0.032f);
    static entt::entity CreateSpotLight(entt::registry &registry, const std::string &name,
                                        const glm::vec3 &position = glm::vec3(0.0f, 3.0f, 3.0f),
                                        const glm::vec3 &color = glm::vec3(1.0f), float intensity = 1.0f,
                                        float constant = 1.0f, float linear = 0.09f, float quadratic = 0.032f,
                                        float cutOff = 12.5f, float outerCutOff = 15.0f);

    // clang-format off
    template <typename... Components>
    // clang-format on
    static entt::entity AddComponents(entt::registry &registry, entt::entity entity, Components &&...components)
    {
        if (!registry.valid(entity) || !registry.try_get<TagComponent>(entity))
        {
            LOG_ENGINE_ERROR("Entity is not valid. Cannot add components.");
            return entt::null;
        }
        (registry.emplace<std::decay_t<Components>>(entity, std::forward<Components>(components)), ...);
        return entity;
    }
};

} // namespace MCEngine