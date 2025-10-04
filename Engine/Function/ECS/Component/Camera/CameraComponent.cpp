#include "CameraComponent.hpp"

MCEngine::CameraComponent::CameraComponent(CameraType type, float width, float height, float fov, float nearClip,
                                           float farClip)
    : m_Type(type), m_Width(width), m_Height(height), m_FOV(fov), m_NearClip(nearClip), m_FarClip(farClip)
{
    UpdateProjectionMatrix();
    LOG_ENGINE_INFO("CameraComponent created with type: " + std::to_string((int)m_Type) +
                    ", FOV: " + std::to_string(m_FOV) + ", nearClip: " + std::to_string(m_NearClip) +
                    ", farClip: " + std::to_string(m_FarClip));
}

void MCEngine::CameraComponent::SetType(CameraType type)
{
    m_Type = type;
    UpdateProjectionMatrix();
}

void MCEngine::CameraComponent::SetScale(float scale)
{
    if (m_Type != CameraType::Orthographic)
    {
        LOG_ENGINE_WARN("Trying to set scale on a non-orthographic camera");
        return;
    }
    m_Scale = scale;
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

void MCEngine::CameraComponent::Resize(float width, float height)
{
    m_Width = width;
    m_Height = height;
    UpdateProjectionMatrix();
}

void MCEngine::CameraComponent::UpdateProjectionMatrix()
{
    ENGINE_PROFILE_FUNCTION();

    if (m_Type == CameraType::Orthographic)
    {
        m_ProjectionMatrix = glm::ortho(-m_Width / 200.0f * m_Scale, m_Width / 200.0f * m_Scale,
                                        -m_Height / 200.0f * m_Scale, m_Height / 200.0f * m_Scale, -1.0f, 1.0f);
    }
    else if (m_Type == CameraType::Perspective)
    {
        m_ProjectionMatrix = glm::perspective(glm::radians(m_FOV), m_Width / m_Height, m_NearClip, m_FarClip);
    }
}