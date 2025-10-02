#pragma once

#include "pch.hpp"

class Entity
{
public:
    Entity(entt::entity handle, entt::registry *registry) : m_Entity(handle), m_Registry(registry) {}

    entt::entity Handle() const { return m_Entity; }

    template <typename T, typename... Args> T &AddComponent(Args &&...args)
    {
        T &component = m_Registry->emplace<T>(m_Entity, std::forward<Args>(args)...);
        m_ComponentTypes.push_back(entt::resolve<T>().type_id());
        return component;
    }

    template <typename T> bool HasComponent() const { return m_Registry->all_of<T>(m_Entity); }

    template <typename T> T &GetComponent() { return m_Registry->get<T>(m_Entity); }

    template <typename T> void RemoveComponent()
    {
        m_Registry->remove<T>(m_Entity);
        // 可选择从 m_ComponentTypes 移除
    }

    const std::vector<entt::id_type> &GetComponentTypes() const { return m_ComponentTypes; }

private:
    entt::entity m_Entity;
    entt::registry *m_Registry;
    std::vector<entt::id_type> m_ComponentTypes; // 用 meta type_id 记录组件
};
