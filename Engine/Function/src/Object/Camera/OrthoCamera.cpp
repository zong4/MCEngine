#include "OrthoCamera.hpp"

MCEngine::OrthoCamera::OrthoCamera(glm::vec3 position, glm::vec2 size) : Object(position), m_Size(size)
{
    m_Projection = glm::ortho(-size.x / 2.0f + position.x, size.x / 2.0f + position.x, -size.y / 2.0f + position.y,
                              size.y / 2.0f + position.y, -1.0f, 1.0f);
    UpdateView();

    LOG_ENGINE_INFO("OrthoCamera created at position (" + std::to_string(position.x) + ", " +
                    std::to_string(position.y) + ", " + std::to_string(position.z) + ") with size (" +
                    std::to_string(size.x) + ", " + std::to_string(size.y) + ").");
}

void MCEngine::OrthoCamera::OnEvent(Event &event) {}

void MCEngine::OrthoCamera::Update() {}

void MCEngine::OrthoCamera::SetPosition(const glm::vec3 &position)
{
    m_Position = position;
    UpdateView();
}

void MCEngine::OrthoCamera::UpdateView()
{
    m_View = glm::lookAt(m_Position, m_Position + glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f));
}