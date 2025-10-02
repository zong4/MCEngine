#pragma once

#include "pch.hpp"

namespace MCEngine
{

class Entity
{
public:
    Entity(entt::entity handle, entt::registry *registry) : m_Entity(handle), m_Registry(registry) {}
    virtual ~Entity()
    {
        m_Entity = entt::null;
        m_Registry = nullptr;
    }

    // Operators
    operator bool() const { return GetHandle() != entt::null; }

    // Getters
    entt::entity GetHandle() const { return m_Entity; }

    // Templates
    template <typename T> bool HasComponent() const { return m_Registry->all_of<T>(m_Entity); }
    template <typename T> T &GetComponent() { return m_Registry->get<T>(m_Entity); }
    template <typename T, typename... Args> T &AddComponent(Args &&...args)
    {
        return m_Registry->emplace<T>(m_Entity, std::forward<Args>(args)...);
    }
    template <typename T> void RemoveComponent() { m_Registry->remove<T>(m_Entity); }

private:
    entt::entity m_Entity = entt::null;
    entt::registry *m_Registry;
};

} // namespace MCEngine
