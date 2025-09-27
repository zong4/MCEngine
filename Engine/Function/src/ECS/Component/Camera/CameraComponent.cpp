#include "CameraComponent.hpp"

void MCEngine::CameraComponent::UpdateViewMatrix(const glm::vec3 &position, const glm::vec3 &rotation)
{
    ENGINE_PROFILE_FUNCTION();

    glm::mat4 rotationX = glm::rotate(glm::mat4(1.0f), glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
    glm::mat4 rotationY = glm::rotate(glm::mat4(1.0f), glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
    glm::mat4 rotationZ = glm::rotate(glm::mat4(1.0f), glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
    glm::mat4 rotationXYZ = rotationZ * rotationY * rotationX;

    glm::vec3 front = glm::normalize(glm::vec3(rotationXYZ * glm::vec4(0.0f, 0.0f, -1.0f, 0.0f)));
    glm::vec3 up = glm::normalize(glm::vec3(rotationXYZ * glm::vec4(0.0f, 1.0f, 0.0f, 0.0f)));

    m_ViewMatrix = glm::lookAt(position, position + front, up);

    LOG_ENGINE_TRACE("Camera Position: " + std::to_string(position.x) + ", " + std::to_string(position.y) + ", " +
                     std::to_string(position.z) + "; Rotation: " + std::to_string(rotation.x) + ", " +
                     std::to_string(rotation.y) + ", " + std::to_string(rotation.z));
}

MCEngine::OrthoCameraComponent::OrthoCameraComponent(const glm::vec3 &size) : m_Size(size) { UpdateProjectionMatrix(); }

void MCEngine::OrthoCameraComponent::SetSize(const glm::vec3 &size)
{
    m_Size = size;
    UpdateProjectionMatrix();
}

void MCEngine::OrthoCameraComponent::UpdateProjectionMatrix()
{
    ENGINE_PROFILE_FUNCTION();

    m_ProjectionMatrix = glm::ortho(-m_Size.x / 2.0f, m_Size.x / 2.0f, -m_Size.y / 2.0f, m_Size.y / 2.0f,
                                    -m_Size.z / 2.0f, m_Size.z / 2.0f);

    LOG_ENGINE_TRACE("Ortho Camera Size: " + std::to_string(m_Size.x) + ", " + std::to_string(m_Size.y) + ", " +
                     std::to_string(m_Size.z));
}

MCEngine::PerspectiveCameraComponent::PerspectiveCameraComponent(float fov, float aspectRatio, float nearClip,
                                                                 float farClip)
    : m_FOV(fov), m_AspectRatio(aspectRatio), m_NearClip(nearClip), m_FarClip(farClip)
{
    UpdateProjectionMatrix();
}

void MCEngine::PerspectiveCameraComponent::SetFOV(float fov)
{
    m_FOV = fov;
    UpdateProjectionMatrix();
}

void MCEngine::PerspectiveCameraComponent::SetAspectRatio(float aspectRatio)
{
    m_AspectRatio = aspectRatio;
    UpdateProjectionMatrix();
}

void MCEngine::PerspectiveCameraComponent::SetNearClip(float nearClip)
{
    m_NearClip = nearClip;
    UpdateProjectionMatrix();
}

void MCEngine::PerspectiveCameraComponent::SetFarClip(float farClip)
{
    m_FarClip = farClip;
    UpdateProjectionMatrix();
}

void MCEngine::PerspectiveCameraComponent::UpdateProjectionMatrix()
{
    ENGINE_PROFILE_FUNCTION();

    m_ProjectionMatrix = glm::perspective(glm::radians(m_FOV), m_AspectRatio, m_NearClip, m_FarClip);

    LOG_ENGINE_TRACE("Perspective Camera FOV: " + std::to_string(m_FOV) +
                     "; Aspect Ratio: " + std::to_string(m_AspectRatio) + "; Near Clip: " + std::to_string(m_NearClip) +
                     "; Far Clip: " + std::to_string(m_FarClip));
}