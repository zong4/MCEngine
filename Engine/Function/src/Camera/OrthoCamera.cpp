#include "OrthoCamera.hpp"

MCEngine::OrthoCamera::OrthoCamera(glm::vec3 size, glm::vec3 position, glm::vec3 rotation)
    : Camera(position, rotation), m_Size(size)
{
    UpdateProjectionMatrix();

    LOG_ENGINE_INFO("OrthoCamera created at position (" + std::to_string(position.x) + ", " +
                    std::to_string(position.y) + ", " + std::to_string(position.z) + ") with size (" +
                    std::to_string(size.x) + ", " + std::to_string(size.y) + ", " + std::to_string(size.z) + ").");
}

void MCEngine::OrthoCamera::SetSize(const glm::vec3 &size)
{
    m_Size = size;
    UpdateProjectionMatrix();

    LOG_ENGINE_TRACE("OrthoCamera size set to (" + std::to_string(size.x) + ", " + std::to_string(size.y) + ", " +
                     std::to_string(size.z) + ").");
}

void MCEngine::OrthoCamera::OnEvent(Event &event)
{
    ENGINE_PROFILE_FUNCTION();

    EventDispatcher dispatcher(event);
    dispatcher.Dispatch<WindowResizeEvent>([this](WindowResizeEvent &e) {
        SetSize(glm::vec3(e.GetWidth() / 100.0f, e.GetHeight() / 100.0f, m_Size.z));
        return true;
    });
}

void MCEngine::OrthoCamera::UpdateProjectionMatrix()
{
    ENGINE_PROFILE_FUNCTION();

    m_Projection =
        glm::ortho(-m_Size.x / 2.0f + m_Position.x, m_Size.x / 2.0f + m_Position.x, -m_Size.y / 2.0f + m_Position.y,
                   m_Size.y / 2.0f + m_Position.y, m_Position.z - m_Size.z / 2.0f, m_Position.z + m_Size.z / 2.0f);
}
