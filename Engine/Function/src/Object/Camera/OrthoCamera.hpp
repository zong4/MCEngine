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

    void Update() override;

private:
    glm::vec2 m_Center;
    glm::vec2 m_Size;
    glm::mat4 m_Projection;
    glm::mat4 m_View;
};

} // namespace MCEngine