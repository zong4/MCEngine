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

    static entt::entity CreateBasicSquare(entt::registry &registry, const std::string &name,
                                          const glm::vec3 &position = glm::vec3(0.0f),
                                          const glm::vec3 &rotation = glm::vec3(0.0f),
                                          const glm::vec3 &scale = glm::vec3(1.0f));
    static entt::entity CreateBasicCube(entt::registry &registry, const std::string &name,
                                        const glm::vec3 &position = glm::vec3(0.0f),
                                        const glm::vec3 &rotation = glm::vec3(0.0f),
                                        const glm::vec3 &scale = glm::vec3(1.0f));

    static entt::entity CreateBasicOrthoCamera(entt::registry &registry, const std::string &name,
                                               const glm::vec3 &position, const glm::vec3 &rotation,
                                               const glm::vec3 &size);
    static entt::entity CreateBasicPerspectiveCamera(entt::registry &registry, const std::string &name,
                                                     const glm::vec3 &position, const glm::vec3 &rotation, float fov,
                                                     float aspectRatio, float nearClip, float farClip);

    static entt::entity CreateBasicPointLight(entt::registry &registry, const std::string &name);

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