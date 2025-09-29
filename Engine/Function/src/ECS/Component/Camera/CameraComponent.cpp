#include "CameraComponent.hpp"

MCEngine::CameraComponent::CameraComponent(TransformComponent *transformComponent, const glm::vec3 &size)
    : m_Type(CameraType::Ortho), m_TransformComponent(transformComponent), m_Size(size)
{
    UpdateViewMatrix();
    UpdateProjectionMatrix();
    LOG_ENGINE_INFO("Ortho Camera Created with Size: " + ToString(size));
}

MCEngine::CameraComponent::CameraComponent(TransformComponent *transformComponent, float fov, float aspectRatio,
                                           float nearClip, float farClip)
    : m_Type(CameraType::Perspective), m_TransformComponent(transformComponent), m_FOV(fov), m_AspectRatio(aspectRatio),
      m_NearClip(nearClip), m_FarClip(farClip)
{
    UpdateViewMatrix();
    UpdateProjectionMatrix();
    LOG_ENGINE_INFO("Perspective Camera Created with FOV: " + std::to_string(fov) +
                    ", Aspect Ratio: " + std::to_string(aspectRatio) + ", Near Clip: " + std::to_string(nearClip) +
                    ", Far Clip: " + std::to_string(farClip));
}

MCEngine::CameraComponent::~CameraComponent() { m_TransformComponent = nullptr; }

void MCEngine::CameraComponent::Update(float deltaTime)
{
    if (m_TransformComponent->IsDirty())
    {
        UpdateViewMatrix();
    }
}

void MCEngine::CameraComponent::Resize(float width, float height)
{
    if (m_Type == CameraType::Ortho)
    {
        m_Size = glm::vec3(width, height, m_Size.z);
    }
    else if (m_Type == CameraType::Perspective)
    {
        m_AspectRatio = width / height;
    }
    UpdateProjectionMatrix();
}

void MCEngine::CameraComponent::SetFOV(float fov)
{
    if (m_Type != CameraType::Perspective)
    {
        LOG_ENGINE_WARN("Trying to set FOV on a non-perspective camera.");
        return;
    }

    m_FOV = fov;
    UpdateProjectionMatrix();
}

void MCEngine::CameraComponent::SetNearClip(float nearClip)
{
    if (m_Type != CameraType::Perspective)
    {
        LOG_ENGINE_WARN("Trying to set Near Clip on a non-perspective camera.");
        return;
    }

    m_NearClip = nearClip;
    UpdateProjectionMatrix();
}

void MCEngine::CameraComponent::SetFarClip(float farClip)
{
    if (m_Type != CameraType::Perspective)
    {
        LOG_ENGINE_WARN("Trying to set Far Clip on a non-perspective camera.");
        return;
    }

    m_FarClip = farClip;
    UpdateProjectionMatrix();
}

void MCEngine::CameraComponent::UpdateViewMatrix()
{
    ENGINE_PROFILE_FUNCTION();

    glm::vec3 position = m_TransformComponent->GetPosition();
    glm::vec3 rotation = m_TransformComponent->GetRotation();

    glm::mat4 rotationX = glm::rotate(glm::mat4(1.0f), glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
    glm::mat4 rotationY = glm::rotate(glm::mat4(1.0f), glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
    glm::mat4 rotationZ = glm::rotate(glm::mat4(1.0f), glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
    glm::mat4 rotationXYZ = rotationZ * rotationY * rotationX;

    glm::vec3 front = glm::normalize(glm::vec3(rotationXYZ * glm::vec4(0.0f, 0.0f, -1.0f, 0.0f)));
    glm::vec3 up = glm::normalize(glm::vec3(rotationXYZ * glm::vec4(0.0f, 1.0f, 0.0f, 0.0f)));

    m_ViewMatrix = glm::lookAt(position, position + front, up);
}

void MCEngine::CameraComponent::UpdateProjectionMatrix()
{
    ENGINE_PROFILE_FUNCTION();

    if (m_Type == CameraType::Ortho)
    {
        m_ProjectionMatrix = glm::ortho(-m_Size.x / 2.0f, m_Size.x / 2.0f, -m_Size.y / 2.0f, m_Size.y / 2.0f,
                                        -m_Size.z / 2.0f, m_Size.z / 2.0f);
    }
    else if (m_Type == CameraType::Perspective)
    {
        m_ProjectionMatrix = glm::perspective(glm::radians(m_FOV), m_AspectRatio, m_NearClip, m_FarClip);
    }
}