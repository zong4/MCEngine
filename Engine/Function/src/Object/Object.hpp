#pragma once

#include "pch.hpp"

namespace MCEngine
{

class Object
{
public:
    Object() = default;
    Object(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale)
        : m_Position(position), m_Rotation(rotation), m_Scale(scale)
    {
    }
    virtual ~Object() = default;

    virtual void Update() = 0;
    virtual void Render(const std::string &pipeline);

protected:
    // Transform
    glm::vec3 m_Position{0.0f, 0.0f, 0.0f};
    glm::vec3 m_Rotation{0.0f, 0.0f, 0.0f};
    glm::vec3 m_Scale{1.0f, 1.0f, 1.0f};

    // Rendering
    std::shared_ptr<VertexArray> m_VertexArray = nullptr;

protected:
    glm::mat4 GetTransform() const;
};

} // namespace MCEngine
