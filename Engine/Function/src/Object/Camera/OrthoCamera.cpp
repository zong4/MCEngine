#include "OrthoCamera.hpp"

MCEngine::OrthoCamera::OrthoCamera(glm::vec3 position, glm::vec2 size) : Camera(position), m_Size(size)
{
    m_Projection = glm::ortho(-size.x / 2.0f + m_Position.x, size.x / 2.0f + m_Position.x,
                              -size.y / 2.0f + m_Position.y, size.y / 2.0f + m_Position.y, -1.0f, 1.0f);
    LOG_ENGINE_TRACE("OrthoCamera created at position (" + std::to_string(position.x) + ", " +
                     std::to_string(position.y) + ", " + std::to_string(position.z) + ") with size (" +
                     std::to_string(size.x) + ", " + std::to_string(size.y) + ").");
}

void MCEngine::OrthoCamera::SetSize(const glm::vec2 &size)
{
    m_Size = size;
    m_Projection = glm::ortho(-size.x / 2.0f + m_Position.x, size.x / 2.0f + m_Position.x,
                              -size.y / 2.0f + m_Position.y, size.y / 2.0f + m_Position.y, -1.0f, 1.0f);
    LOG_ENGINE_TRACE("OrthoCamera size set to (" + std::to_string(size.x) + ", " + std::to_string(size.y) + ").");
}

void MCEngine::OrthoCamera::OnEvent(Event &event)
{
    EventDispatcher dispatcher(event);

    dispatcher.Dispatch<WindowResizeEvent>([this](WindowResizeEvent &e) {
        SetSize(glm::vec2(e.GetWidth() / 100.0f, e.GetHeight() / 100.0f));
        return true;
    });
}

void MCEngine::OrthoCamera::Update() {}
