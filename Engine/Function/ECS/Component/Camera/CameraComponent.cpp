#include "CameraComponent.hpp"

MCEngine::CameraComponent::CameraComponent(const glm::vec3 &size) : m_Type(CameraType::Ortho), m_Size(size)
{
    UpdateProjectionMatrix();
    LOG_ENGINE_INFO("Ortho Camera Created with Size: " + ToString(size));
}

MCEngine::CameraComponent::CameraComponent(float fov, float aspectRatio, float nearClip, float farClip)
    : m_Type(CameraType::Perspective), m_FOV(fov), m_AspectRatio(aspectRatio), m_NearClip(nearClip), m_FarClip(farClip)
{
    UpdateProjectionMatrix();
    LOG_ENGINE_INFO("Perspective Camera Created with FOV: " + std::to_string(fov) +
                    ", Aspect Ratio: " + std::to_string(aspectRatio) + ", Near Clip: " + std::to_string(nearClip) +
                    ", Far Clip: " + std::to_string(farClip));
}

MCEngine::CameraComponent::~CameraComponent() {}

void MCEngine::CameraComponent::Update(float deltaTime) {}

void MCEngine::CameraComponent::Resize(float width, float height)
{
    if (m_Type == CameraType::Ortho)
    {
        m_Size = glm::vec3(width / 100.0f, height / 100.0f, m_Size.z);
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
        LOG_ENGINE_WARN("Trying to set FOV on a non-perspective camera");
        return;
    }
    m_FOV = fov;
    UpdateProjectionMatrix();
}

void MCEngine::CameraComponent::SetNearClip(float nearClip)
{
    if (m_Type != CameraType::Perspective)
    {
        LOG_ENGINE_WARN("Trying to set Near Clip on a non-perspective camera");
        return;
    }
    m_NearClip = nearClip;
    UpdateProjectionMatrix();
}

void MCEngine::CameraComponent::SetFarClip(float farClip)
{
    if (m_Type != CameraType::Perspective)
    {
        LOG_ENGINE_WARN("Trying to set Far Clip on a non-perspective camera");
        return;
    }
    m_FarClip = farClip;
    UpdateProjectionMatrix();
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