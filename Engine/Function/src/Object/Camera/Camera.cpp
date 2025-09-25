#include "Camera.hpp"

MCEngine::Camera::Camera(glm::vec3 position) : Object(position) { UpdateViewMatrix(); }

void MCEngine::Camera::SetPosition(const glm::vec3 &position)
{
    m_Position = position;
    UpdateViewMatrix();
}

void MCEngine::Camera::SetRotation(const glm::vec3 &rotation)
{
    m_Rotation = rotation;
    UpdateViewMatrix();
}

void MCEngine::Camera::UpdateViewMatrix()
{
    glm::mat4 rotationX = glm::rotate(glm::mat4(1.0f), glm::radians(m_Rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
    glm::mat4 rotationY = glm::rotate(glm::mat4(1.0f), glm::radians(m_Rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
    glm::mat4 rotationZ = glm::rotate(glm::mat4(1.0f), glm::radians(m_Rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
    glm::mat4 rotation = rotationZ * rotationY * rotationX;

    glm::vec3 front = glm::normalize(glm::vec3(rotation * glm::vec4(0.0f, 0.0f, -1.0f, 0.0f)));
    glm::vec3 up = glm::normalize(glm::vec3(rotation * glm::vec4(0.0f, 1.0f, 0.0f, 0.0f)));

    m_View = glm::lookAt(m_Position, m_Position + front, up);
}