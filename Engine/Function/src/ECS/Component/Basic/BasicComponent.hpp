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

    virtual void Update(float deltaTime) override {}

private:
    std::string m_Tag;
};

class TransformComponent : public Component
{
public:
    TransformComponent(const glm::vec3 &position, const glm::vec3 &rotation, const glm::vec3 &scale);

    bool IsDirty() const { return m_Dirty; }
    glm::vec3 &GetPosition();
    glm::vec3 &GetRotation();
    glm::vec3 &GetScale();
    const glm::vec3 &GetPosition() const { return m_Position; }
    const glm::vec3 &GetRotation() const { return m_Rotation; }
    const glm::vec3 &GetScale() const { return m_Scale; }
    glm::vec3 GetForward() const;
    glm::vec3 GetRight() const;
    glm::vec3 GetUp() const;
    glm::mat4 GetTransformMatrix() const;

    void SetDirty(bool dirty) { m_Dirty = dirty; }
    void SetPosition(const glm::vec3 &position);
    void SetRotation(const glm::vec3 &rotation);
    void SetScale(const glm::vec3 &scale);

    virtual void Update(float deltaTime) override;

private:
    bool m_Dirty = true;
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
    const std::vector<entt::entity> &GetChildren() const { return m_Children; }

    void SetParent(entt::entity parent) { m_Parent = parent; }
    void AddChild(entt::entity child) { m_Children.push_back(child); }
    void RemoveChild(entt::entity child);

    virtual void Update(float deltaTime) override {}

private:
    entt::entity m_Parent;
    std::vector<entt::entity> m_Children;
};

} // namespace MCEngine