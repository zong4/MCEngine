#include "TransformComponent.hpp"

MCEngine::TransformComponent::TransformComponent(const glm::vec3 &position, const glm::vec3 &rotation,
                                                 const glm::vec3 &scale)
    : m_Position(position), m_Rotation(rotation), m_Scale(scale)
{
    LOG_ENGINE_INFO("Transform Component created with Position: " + ToString(m_Position) +
                    ", Rotation: " + ToString(m_Rotation) + ", Scale: " + ToString(m_Scale));
}

glm::mat4 MCEngine::TransformComponent::GetTransformMatrix() const
{
    ENGINE_PROFILE_FUNCTION();

    glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f), m_Position);

    glm::mat4 rotationX = glm::rotate(glm::mat4(1.0f), glm::radians(m_Rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
    glm::mat4 rotationY = glm::rotate(glm::mat4(1.0f), glm::radians(m_Rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
    glm::mat4 rotationZ = glm::rotate(glm::mat4(1.0f), glm::radians(m_Rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
    glm::mat4 rotationMatrix = rotationZ * rotationY * rotationX;

    glm::mat4 scaleMatrix = glm::scale(glm::mat4(1.0f), m_Scale);

    return translationMatrix * rotationMatrix * scaleMatrix;
}