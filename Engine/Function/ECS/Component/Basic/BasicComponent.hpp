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
    RelationshipComponent(Entity parent = Entity()) : m_Parent(parent) {}

    // Getters
    Entity GetParent() const { return m_Parent; }
    const std::vector<Entity> &GetChildren() const { return m_Children; }

    // Setters
    void SetParent(Entity parent) { m_Parent = parent; }
    void AddChild(Entity child) { m_Children.push_back(child); }
    void RemoveChild(Entity child);

private:
    Entity m_Parent;
    std::vector<Entity> m_Children;
};

class NativeScriptComponent
{
public:
    NativeScriptComponent() = default;
    std::function<std::shared_ptr<ScriptableEntity>()> InstantiateScript;
    std::function<void()> DestroyScript;

public:
    // clang-format off
    template <typename T>
    // clang-format on
    void Bind()
    {
        InstantiateScript = [&]() {
            Instance = std::make_shared<T>();
            return Instance;
        };
        DestroyScript = [&]() { Instance->OnDestroy(); };
    }

public:
    std::shared_ptr<ScriptableEntity> Instance;
};

} // namespace MCEngine