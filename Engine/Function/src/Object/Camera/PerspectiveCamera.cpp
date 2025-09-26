#include "PerspectiveCamera.hpp"

MCEngine::PerspectiveCamera::PerspectiveCamera(glm::vec3 position, float fov, float aspectRatio, float nearClip,
                                               float farClip)
    : Camera(position), m_FOV(fov), m_AspectRatio(aspectRatio), m_NearClip(nearClip), m_FarClip(farClip)
{
    UpdateProjectionMatrix();

    LOG_ENGINE_TRACE("PerspectiveCamera created at position (" + std::to_string(position.x) + ", " +
                     std::to_string(position.y) + ", " + std::to_string(position.z) + ") with FOV " +
                     std::to_string(fov) + ", aspect ratio " + std::to_string(aspectRatio) + ", near clip " +
                     std::to_string(nearClip) + ", far clip " + std::to_string(farClip) + ".");
}

void MCEngine::PerspectiveCamera::SetFOV(float fov)
{
    m_FOV = fov;
    UpdateProjectionMatrix();

    LOG_ENGINE_TRACE("PerspectiveCamera FOV set to " + std::to_string(fov) + ".");
}

void MCEngine::PerspectiveCamera::SetAspectRatio(float aspectRatio)
{
    m_AspectRatio = aspectRatio;
    UpdateProjectionMatrix();

    LOG_ENGINE_TRACE("PerspectiveCamera aspect ratio set to " + std::to_string(aspectRatio) + ".");
}

void MCEngine::PerspectiveCamera::SetNearClip(float nearClip)
{
    m_NearClip = nearClip;
    UpdateProjectionMatrix();

    LOG_ENGINE_TRACE("PerspectiveCamera near clip set to " + std::to_string(nearClip) + ".");
}

void MCEngine::PerspectiveCamera::SetFarClip(float farClip)
{
    m_FarClip = farClip;
    UpdateProjectionMatrix();

    LOG_ENGINE_TRACE("PerspectiveCamera far clip set to " + std::to_string(farClip) + ".");
}

void MCEngine::PerspectiveCamera::OnEvent(Event &event)
{
    ENGINE_PROFILE_FUNCTION();

    EventDispatcher dispatcher(event);
    dispatcher.Dispatch<WindowResizeEvent>([this](WindowResizeEvent &e) {
        SetAspectRatio(static_cast<float>(e.GetWidth()) / static_cast<float>(e.GetHeight()));
        return true;
    });
}

void MCEngine::PerspectiveCamera::UpdateProjectionMatrix()
{
    ENGINE_PROFILE_FUNCTION();

    m_Projection = glm::perspective(glm::radians(m_FOV), m_AspectRatio, m_NearClip, m_FarClip);
}