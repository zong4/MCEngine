#pragma once

#include "pch.hpp"

namespace MCEngine
{

class Entity
{
public:
    Entity() = default;
    Entity(entt::entity handle, entt::registry *registry) : m_Entity(handle), m_Registry(registry) {}
    virtual ~Entity() { m_Registry = nullptr; }

    // Operators
    operator bool() const { return m_Entity != entt::null; }
    operator entt::entity() const { return m_Entity; }
    bool operator==(const Entity &other) const { return m_Entity == other.m_Entity; }
    bool operator!=(const Entity &other) const { return !(*this == other); }

    // Getters
    entt::entity GetHandle() const { return m_Entity; }

public:
    // clang-format off
    template <typename T>
    // clang-format on
    bool HasComponent() const
    {
        if (!m_Registry)
            return false;
        return m_Registry->all_of<T>(m_Entity);
    }
    // clang-format off
    template <typename T>
    // clang-format on
    T &GetComponent() const
    {
        return m_Registry->get<T>(m_Entity);
    }
    // clang-format off
    template <typename T, typename... Args>
    // clang-format on
    T &AddComponent(Args &&...args)
    {
        return m_Registry->emplace<T>(m_Entity, std::forward<Args>(args)...);
    }
    // clang-format off
    template <typename T>
    // clang-format on
    void RemoveComponent()
    {
        m_Registry->remove<T>(m_Entity);
    }

protected:
    entt::entity m_Entity = entt::null;
    entt::registry *m_Registry = nullptr;
};

} // namespace MCEngine
