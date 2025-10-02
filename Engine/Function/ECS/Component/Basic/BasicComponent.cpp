#include "BasicComponent.hpp"

MCEngine::TagComponent::TagComponent(const std::string &tag) : m_Tag(tag)
{
    LOG_ENGINE_INFO("Tag Component created with Tag: " + m_Tag);
}

MCEngine::TransformComponent::TransformComponent(const glm::vec3 &position, const glm::vec3 &rotation,
                                                 const glm::vec3 &scale)
    : m_Position(position), m_Rotation(rotation), m_Scale(scale)
{
    LOG_ENGINE_INFO("Transform Component created with Position: " + ToString(m_Position) +
                    ", Rotation: " + ToString(m_Rotation) + ", Scale: " + ToString(m_Scale));
}

glm::vec3 MCEngine::TransformComponent::GetForward() const
{
    ENGINE_PROFILE_FUNCTION();

    return glm::normalize(glm::vec3(m_RotationMatrix * glm::vec4(0.0f, 0.0f, -1.0f, 0.0f)));
}

glm::vec3 MCEngine::TransformComponent::GetRight() const
{
    ENGINE_PROFILE_FUNCTION();

    return glm::normalize(glm::vec3(m_RotationMatrix * glm::vec4(1.0f, 0.0f, 0.0f, 0.0f)));
}

glm::vec3 MCEngine::TransformComponent::GetUp() const
{
    ENGINE_PROFILE_FUNCTION();

    return glm::normalize(glm::vec3(m_RotationMatrix * glm::vec4(0.0f, 1.0f, 0.0f, 0.0f)));
}

void MCEngine::TransformComponent::UpdateTransformMatrix()
{
    ENGINE_PROFILE_FUNCTION();

    glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f), m_Position);

    glm::mat4 rotationX = glm::rotate(glm::mat4(1.0f), glm::radians(m_Rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
    glm::mat4 rotationY = glm::rotate(glm::mat4(1.0f), glm::radians(m_Rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
    glm::mat4 rotationZ = glm::rotate(glm::mat4(1.0f), glm::radians(m_Rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
    m_RotationMatrix = rotationZ * rotationY * rotationX;

    glm::mat4 scaleMatrix = glm::scale(glm::mat4(1.0f), m_Scale);

    m_TransformMatrix = translationMatrix * m_RotationMatrix * scaleMatrix;
}

void MCEngine::TransformComponent::UpdateViewMatrix()
{
    ENGINE_PROFILE_FUNCTION();

    m_ViewMatrix = glm::lookAt(m_Position, m_Position + GetForward(), GetUp());
}

void MCEngine::RelationshipComponent::RemoveChild(Entity child)
{
    ENGINE_PROFILE_FUNCTION();

    m_Children.erase(std::remove(m_Children.begin(), m_Children.end(), child), m_Children.end());
}