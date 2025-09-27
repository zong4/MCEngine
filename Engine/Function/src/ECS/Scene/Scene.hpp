#pragma once

#include "pch.hpp"

namespace MCEngine
{

class Scene
{
public:
    Scene() = default;
    virtual ~Scene() = default;

public:
    virtual void OnEvent(Event &event) = 0;
    virtual void Update(float deltaTime) = 0;
    virtual void Render() const = 0;

    // clang-format off
    template <typename... Components>
    // clang-format on
    entt::entity CreateEntity(Components &&...components)
    {
        entt::entity entity = m_Registry.create();
        (m_Registry.emplace<std::decay_t<Components>>(entity, std::forward<Components>(components)), ...);
        return entity;
    }

    // clang-format off
    template <typename... Components>
    // clang-format on
    void AddComponent(entt::entity entity, Components &&...components)
    {
        (m_Registry.emplace<std::decay_t<Components>>(entity, std::forward<Components>(components)), ...);
    }

protected:
    entt::registry m_Registry = {};
    entt::entity m_MainCamera;
};

} // namespace MCEngine