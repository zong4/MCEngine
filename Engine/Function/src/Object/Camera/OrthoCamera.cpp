#include "OrthoCamera.hpp"

MCEngine::OrthoCamera::OrthoCamera(glm::vec2 center, glm::vec2 size)
    : Object(glm::vec3(center, -10.0f)), m_Center(center), m_Size(size)
{
    m_Projection = glm::ortho(-size.x / 2.0f + center.x, size.x / 2.0f + center.x, -size.y / 2.0f + center.y,
                              size.y / 2.0f + center.y, -1.0f, 1.0f);
    m_View = glm::mat4(1.0f);
}

void MCEngine::OrthoCamera::Update() {}