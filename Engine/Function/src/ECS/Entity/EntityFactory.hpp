#pragma once

#include "pch.hpp"

namespace MCEngine
{

class EntityFactory
{
public:
    // clang-format off
    template <typename... Components>
    // clang-format on
    static entt::entity CreateEntity(entt::registry &registry, Components &&...components)
    {
        entt::entity entity = registry.create();
        (registry.emplace<std::decay_t<Components>>(entity, std::forward<Components>(components)), ...);
        return entity;
    }
};

} // namespace MCEngine