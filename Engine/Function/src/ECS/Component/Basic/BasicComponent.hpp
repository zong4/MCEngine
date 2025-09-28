#pragma once

#include "ECS/Component/Component.hpp"

namespace MCEngine
{

class TagComponent : public Component
{
public:
    TagComponent(const std::string &tag);

    const std::string &GetTag() const { return m_Tag; }
    void SetTag(const std::string &tag) { m_Tag = tag; }

private:
    std::string m_Tag;
};

class TransformComponent : public Component
{
public:
    TransformComponent(const glm::vec3 &position = glm::vec3(0.0f), const glm::vec3 &rotation = glm::vec3(0.0f),
                       const glm::vec3 &scale = glm::vec3(1.0f));

    const glm::vec3 &GetPosition() const { return m_Position; }
    const glm::vec3 &GetRotation() const { return m_Rotation; }
    const glm::vec3 &GetScale() const { return m_Scale; }
    glm::mat4 GetTransformMatrix() const;

    void SetPosition(const glm::vec3 &position) { m_Position = position; }
    void SetRotation(const glm::vec3 &rotation) { m_Rotation = rotation; }
    void SetScale(const glm::vec3 &scale) { m_Scale = scale; }

private:
    glm::vec3 m_Position;
    glm::vec3 m_Rotation;
    glm::vec3 m_Scale;
};

// todo
class RelationshipComponent : public Component
{
public:
    RelationshipComponent(entt::entity parent = entt::null) : m_Parent(parent) {}

    entt::entity GetParent() const { return m_Parent; }
    void SetParent(entt::entity parent) { m_Parent = parent; }

    const std::vector<entt::entity> &GetChildren() const { return m_Children; }
    void AddChild(entt::entity child) { m_Children.push_back(child); }
    void RemoveChild(entt::entity child)
    {
        m_Children.erase(std::remove(m_Children.begin(), m_Children.end(), child), m_Children.end());
    }

private:
    entt::entity m_Parent;
    std::vector<entt::entity> m_Children;
};

} // namespace MCEngine