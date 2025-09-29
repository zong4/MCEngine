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

glm::vec3 &MCEngine::TransformComponent::GetPosition()
{
    SetDirty(true);
    return m_Position;
}

glm::vec3 &MCEngine::TransformComponent::GetRotation()
{
    SetDirty(true);
    return m_Rotation;
}

glm::vec3 &MCEngine::TransformComponent::GetScale()
{
    SetDirty(true);
    return m_Scale;
}

void MCEngine::TransformComponent::SetPosition(const glm::vec3 &position)
{
    m_Position = position;
    SetDirty(true);
}

void MCEngine::TransformComponent::SetRotation(const glm::vec3 &rotation)
{
    m_Rotation = rotation;
    SetDirty(true);
}

void MCEngine::TransformComponent::SetScale(const glm::vec3 &scale)
{
    m_Scale = scale;
    SetDirty(true);
}

void MCEngine::TransformComponent::Update(float deltaTime)
{
    if (m_Dirty)
    {
        UpdateTransformMatrix();
        UpdateRotationMatrix();
        m_Dirty = false;
    }
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
    glm::mat4 rotationMatrix = rotationZ * rotationY * rotationX;

    glm::mat4 scaleMatrix = glm::scale(glm::mat4(1.0f), m_Scale);

    m_TransformMatrix = translationMatrix * rotationMatrix * scaleMatrix;
}

void MCEngine::TransformComponent::UpdateRotationMatrix()
{
    ENGINE_PROFILE_FUNCTION();

    glm::mat4 rotationX = glm::rotate(glm::mat4(1.0f), glm::radians(m_Rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
    glm::mat4 rotationY = glm::rotate(glm::mat4(1.0f), glm::radians(m_Rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
    glm::mat4 rotationZ = glm::rotate(glm::mat4(1.0f), glm::radians(m_Rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
    m_RotationMatrix = rotationZ * rotationY * rotationX;
}

void MCEngine::RelationshipComponent::RemoveChild(entt::entity child)
{
    m_Children.erase(std::remove(m_Children.begin(), m_Children.end(), child), m_Children.end());
}