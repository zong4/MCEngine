#pragma once

#include "pch.hpp"

namespace MCEngine
{

class Camera
{
public:
    Camera(glm::vec3 position = glm::vec3(0.0f), glm::vec3 rotation = glm::vec3(0.0f));
    virtual ~Camera() = default;

    glm::vec3 GetPosition() const { return m_Position; }
    glm::vec3 GetRotation() const { return m_Rotation; }
    glm::mat4 GetView() const { return m_View; }
    glm::mat4 GetProjection() const { return m_Projection; }

    void SetPosition(const glm::vec3 &position);
    void SetRotation(const glm::vec3 &rotation);

public:
    virtual void OnEvent(Event &event) = 0;
    virtual void Update(float deltaTime) = 0;

protected:
    glm::vec3 m_Position;
    glm::vec3 m_Rotation;
    glm::mat4 m_View;
    glm::mat4 m_Projection;

protected:
    void UpdateViewMatrix();
    virtual void UpdateProjectionMatrix() = 0;
};

} // namespace MCEngine