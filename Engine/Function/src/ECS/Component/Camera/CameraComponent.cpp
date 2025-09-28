#include "CameraComponent.hpp"

MCEngine::CameraComponent::CameraComponent(TransformComponent *transformComponent)
    : m_TransformComponent(transformComponent)
{
    UpdateViewMatrix(m_TransformComponent->GetPosition(), m_TransformComponent->GetRotation());
}

MCEngine::CameraComponent::~CameraComponent() { m_TransformComponent = nullptr; }

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
}

void MCEngine::CameraComponent::Update(float deltaTime)
{
    if (m_TransformComponent->IsDirty())
    {
        UpdateViewMatrix(m_TransformComponent->GetPosition(), m_TransformComponent->GetRotation());
        UpdateProjectionMatrix();
    }
}

MCEngine::OrthoCameraComponent::OrthoCameraComponent(TransformComponent *transformComponent, const glm::vec3 &size)
    : CameraComponent(transformComponent), m_Size(size)
{
    UpdateProjectionMatrix();
    LOG_ENGINE_INFO("Ortho Camera Created with Size: " + ToString(size));
}

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
}

MCEngine::PerspectiveCameraComponent::PerspectiveCameraComponent(TransformComponent *transformComponent, float fov,
                                                                 float aspectRatio, float nearClip, float farClip)
    : CameraComponent(transformComponent), m_FOV(fov), m_AspectRatio(aspectRatio), m_NearClip(nearClip),
      m_FarClip(farClip)
{
    UpdateProjectionMatrix();
    LOG_ENGINE_INFO("Perspective Camera Created with FOV: " + std::to_string(fov) +
                    ", Aspect Ratio: " + std::to_string(aspectRatio) + ", Near Clip: " + std::to_string(nearClip) +
                    ", Far Clip: " + std::to_string(farClip));
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
}