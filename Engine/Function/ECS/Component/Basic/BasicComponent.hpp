#pragma once

#include "ECS/Entity/ScriptableEntity.hpp"

namespace MCEngine
{

class TagComponent
{
public:
    TagComponent(const std::string &tag);

    const std::string &GetTag() const { return m_Tag; }
    void SetTag(const std::string &tag) { m_Tag = tag; }

private:
    std::string m_Tag;
};

class TransformComponent
{
public:
    TransformComponent(const glm::vec3 &position = glm::vec3(0.0f), const glm::vec3 &rotation = glm::vec3(0.0f),
                       const glm::vec3 &scale = glm::vec3(1.0f));

    // Getters
    glm::vec3 &GetPosition() { return m_Position; }
    glm::vec3 &GetRotation() { return m_Rotation; }
    glm::vec3 &GetScale() { return m_Scale; }
    const glm::vec3 &GetPosition() const { return m_Position; }
    const glm::vec3 &GetRotation() const { return m_Rotation; }
    const glm::vec3 &GetScale() const { return m_Scale; }
    const glm::mat4 &GetTransformMatrix() const { return m_TransformMatrix; }
    const glm::mat4 &GetRotationMatrix() const { return m_RotationMatrix; }
    const glm::mat4 &GetViewMatrix() const { return m_ViewMatrix; }
    glm::vec3 GetForward() const;
    glm::vec3 GetRight() const;
    glm::vec3 GetUp() const;

    // Setters
    void SetPosition(const glm::vec3 &position) { m_Position = position; }
    void SetRotation(const glm::vec3 &rotation) { m_Rotation = rotation; }
    void SetScale(const glm::vec3 &scale) { m_Scale = scale; }

public:
    void UpdateTransformMatrix();
    void UpdateViewMatrix();

private:
    glm::vec3 m_Position;
    glm::vec3 m_Rotation;
    glm::vec3 m_Scale;
    glm::mat4 m_TransformMatrix = glm::mat4(1.0f);
    glm::mat4 m_RotationMatrix = glm::mat4(1.0f);
    glm::mat4 m_ViewMatrix = glm::mat4(1.0f);
};

class RelationshipComponent
{
public:
    RelationshipComponent(entt::entity parent = entt::null) : m_Parent(parent) {}

    // Getters
    entt::entity GetParent() const { return m_Parent; }
    const std::vector<entt::entity> &GetChildren() const { return m_Children; }

    // Setters
    void SetParent(entt::entity parent) { m_Parent = parent; }
    void AddChild(entt::entity child) { m_Children.push_back(child); }
    void RemoveChild(entt::entity child);

private:
    entt::entity m_Parent;
    std::vector<entt::entity> m_Children;
};

struct NativeScriptComponent
{
    ScriptableEntity *(*InstantiateScript)();
    void (*DestroyScript)(NativeScriptComponent *);

    template <typename T> void Bind()
    {
        InstantiateScript = []() { return static_cast<ScriptableEntity *>(new T()); };
        DestroyScript = [](NativeScriptComponent *nsc) {
            delete nsc->Instance;
            nsc->Instance = nullptr;
        };
    }

private:
    ScriptableEntity *Instance = nullptr;
};

} // namespace MCEngine