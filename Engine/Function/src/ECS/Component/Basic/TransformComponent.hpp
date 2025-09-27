#pragma once

#include "ECS/Component/Component.hpp"

namespace MCEngine
{

class TransformComponent : public Component
{
public:
    TransformComponent(const glm::vec3 &position = glm::vec3(0.0f), const glm::vec3 &rotation = glm::vec3(0.0f),
                       const glm::vec3 &scale = glm::vec3(1.0f));
    virtual ~TransformComponent() override = default;

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

} // namespace MCEngine