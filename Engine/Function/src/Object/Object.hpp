#pragma once

#include "pch.hpp"

namespace MCEngine
{

class Object
{
public:
    Object(glm::vec3 position = glm::vec3(0.0f), glm::vec3 rotation = glm::vec3(0.0f),
           glm::vec3 scale = glm::vec3(1.0f));
    virtual ~Object() = default;

    glm::vec3 GetPosition() const { return m_Position; }
    glm::vec3 GetRotation() const { return m_Rotation; }
    glm::vec3 GetScale() const { return m_Scale; }

    virtual void SetPosition(const glm::vec3 &position) { m_Position = position; }
    virtual void SetRotation(const glm::vec3 &rotation) { m_Rotation = rotation; }
    virtual void SetScale(const glm::vec3 &scale) { m_Scale = scale; }

public:
    virtual void OnEvent(Event &event) = 0;
    virtual void Update(float deltaTime) = 0;
    virtual void Render(const std::string &pipeline);

protected:
    int m_ID;

    // Transform
    glm::vec3 m_Position;
    glm::vec3 m_Rotation; // in degrees
    glm::vec3 m_Scale;

    // Rendering
    std::shared_ptr<VertexArray> m_VertexArray = nullptr;

protected:
    glm::mat4 GetTransform() const;
};

} // namespace MCEngine
