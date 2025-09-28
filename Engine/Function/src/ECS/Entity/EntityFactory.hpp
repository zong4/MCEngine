#pragma once

#include "ECS/Component/Basic/BasicComponent.hpp"

namespace MCEngine
{

class EntityFactory
{
public:
    // clang-format off
    template <typename... Components>
    // clang-format on
    static entt::entity CreateEntity(entt::registry &registry, const std::string &name, const glm::vec3 &position,
                                     const glm::vec3 &rotation = glm::vec3(0.0f),
                                     const glm::vec3 &scale = glm::vec3(1.0f), Components &&...components)
    {
        entt::entity entity = registry.create();

        registry.emplace<TagComponent>(entity, name);
        registry.emplace<TransformComponent>(entity, position, rotation, scale);
        (registry.emplace<std::decay_t<Components>>(entity, std::forward<Components>(components)), ...);
        registry.emplace<RelationshipComponent>(entity);

        LOG_ENGINE_INFO("Entity created with ID: " + std::to_string((uint32_t)entity) + " and " +
                        std::to_string(sizeof...(Components)) + " components.");

        return entity;
    }

    // clang-format off
    template <typename... Components>
    // clang-format on
    static entt::entity CreateEntity(entt::registry &registry, const std::string &name,
                                     const TransformComponent &transform, Components &&...components)
    {
        entt::entity entity = registry.create();

        registry.emplace<TagComponent>(entity, name);
        registry.emplace<TransformComponent>(entity, transform);
        (registry.emplace<std::decay_t<Components>>(entity, std::forward<Components>(components)), ...);
        registry.emplace<RelationshipComponent>(entity);

        LOG_ENGINE_INFO("Entity created with ID: " + std::to_string((uint32_t)entity) + " and " +
                        std::to_string(sizeof...(Components)) + " components.");

        return entity;
    }
};

} // namespace MCEngine