#pragma once

#include "Object/Object.hpp"

namespace MCEngine
{

class OrthoCamera : public Object
{
public:
    OrthoCamera(glm::vec2 center, glm::vec2 size);
    virtual ~OrthoCamera() override = default;

    glm::mat4 GetProjection() const { return m_Projection; }
    glm::mat4 GetView() const { return m_View; }

public:
    void Update() override;

    void SetPosition(const glm::vec3 &position);
    glm::vec3 GetPosition() const { return m_Position; }

private:
    glm::vec2 m_Center;
    glm::vec2 m_Size;
    glm::mat4 m_Projection;
    glm::mat4 m_View;
};

} // namespace MCEngine