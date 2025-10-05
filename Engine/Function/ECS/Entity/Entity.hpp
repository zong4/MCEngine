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
    operator bool() const { return m_Entity != entt::null && m_Registry && m_Registry->valid(m_Entity); }
    operator uint32_t() const { return (uint32_t)m_Entity; }
    operator entt::entity() const { return m_Entity; }
    bool operator==(const Entity &other) const { return m_Entity == other.m_Entity; }
    bool operator!=(const Entity &other) const { return !(*this == other); }

    // Getters
    // bool IsValid() const { return m_Entity != entt::null && m_Registry && m_Registry->valid(m_Entity); }
    entt::entity GetHandle() const { return m_Entity; }
    entt::registry &GetRegistry() const { return *m_Registry; }
    void SetHandle(entt::entity handle) { m_Entity = handle; }

public:
    // clang-format off
    template <typename T>
    // clang-format on
    bool HasComponent() const
    {
        if (!m_Registry || m_Entity == entt::null || !m_Registry->valid(m_Entity))
            return false;
        return m_Registry->all_of<T>(m_Entity);
    }
    // clang-format off
    template <typename T>
    // clang-format on
    T &GetComponent() const
    {
        if (HasComponent<T>() == false)
            LOG_ENGINE_INFO("Entity does not have component!");
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
