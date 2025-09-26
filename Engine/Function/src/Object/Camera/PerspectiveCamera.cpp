#include "PerspectiveCamera.hpp"

MCEngine::PerspectiveCamera::PerspectiveCamera(glm::vec3 position, float fov, float aspectRatio, float nearClip,
                                               float farClip)
    : Camera(position), m_FOV(fov), m_AspectRatio(aspectRatio), m_NearClip(nearClip), m_FarClip(farClip)
{
    m_Projection = glm::perspective(glm::radians(m_FOV), m_AspectRatio, m_NearClip, m_FarClip);
    LOG_ENGINE_TRACE("PerspectiveCamera created at position (" + std::to_string(position.x) + ", " +
                     std::to_string(position.y) + ", " + std::to_string(position.z) + ") with FOV " +
                     std::to_string(fov) + ", aspect ratio " + std::to_string(aspectRatio) + ", near clip " +
                     std::to_string(nearClip) + ", far clip " + std::to_string(farClip) + ".");
}

void MCEngine::PerspectiveCamera::OnEvent(Event &event)
{
    EventDispatcher dispatcher(event);

    dispatcher.Dispatch<WindowResizeEvent>([this](WindowResizeEvent &e) {
        m_AspectRatio = static_cast<float>(e.GetWidth()) / static_cast<float>(e.GetHeight());
        m_Projection = glm::perspective(glm::radians(m_FOV), m_AspectRatio, m_NearClip, m_FarClip);
        return true;
    });
}

void MCEngine::PerspectiveCamera::Update(float deltaTime) {}