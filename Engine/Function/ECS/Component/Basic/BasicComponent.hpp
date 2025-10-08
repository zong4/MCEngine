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

class TransformComponent
{
public:
    TransformComponent(const glm::vec3 &position = glm::vec3(0.0f), const glm::vec3 &rotation = glm::vec3(0.0f),
                       const glm::vec3 &scale = glm::vec3(1.0f));

    // Getters
    const glm::vec3 &GetPosition() const { return m_Position; }
    const glm::vec3 &GetRotation() const { return m_Rotation; }
    const glm::vec3 &GetScale() const { return m_Scale; }
    const glm::mat4 &GetTransformMatrix() const { return m_TransformMatrix; }
    glm::vec3 GetForward() const { return glm::normalize(m_GlobalRotationQuat * glm::vec3(0, 0, -1)); }
    glm::vec3 GetRight() const { return glm::normalize(m_GlobalRotationQuat * glm::vec3(1, 0, 0)); }
    glm::vec3 GetUp() const { return glm::normalize(m_GlobalRotationQuat * glm::vec3(0, 1, 0)); }

    // Setters
    void SetPosition(const glm::vec3 &position) { m_Position = position; }
    void SetRotationQuat(const glm::quat &quat);
    void SetRotationEuler(const glm::vec3 &euler);
    void SetScale(const glm::vec3 &scale) { m_Scale = glm::max(scale, glm::vec3(0.001f)); }

public:
    void UpdateTransformMatrix(const glm::mat4 &parentTransformMatrix, const glm::quat &parentRotationMatrix,
                               const RelationshipComponent &relationship);

private:
    glm::vec3 m_Position;
    glm::vec3 m_Rotation;
    glm::vec3 m_Scale;
    glm::quat m_RotationQuat;
    glm::quat m_GlobalRotationQuat;
    glm::mat4 m_TransformMatrix = glm::mat4(1.0f);
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