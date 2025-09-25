#include "OrthoCamera.hpp"

MCEngine::OrthoCamera::OrthoCamera(glm::vec3 position, glm::vec2 size)
{
    SetPosition(position);
    SetSize(size);

    LOG_ENGINE_INFO("OrthoCamera created at position (" + std::to_string(position.x) + ", " +
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

void MCEngine::OrthoCamera::SetPosition(const glm::vec3 &position)
{
    Object::SetPosition(position);
    UpdateView();
}

void MCEngine::OrthoCamera::OnEvent(Event &event) {}

void MCEngine::OrthoCamera::Update() {}

void MCEngine::OrthoCamera::UpdateView()
{
    m_View = glm::lookAt(m_Position, m_Position + glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f));
}