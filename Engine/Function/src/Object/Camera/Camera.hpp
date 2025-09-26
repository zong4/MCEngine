#pragma once

#include "Object/Object.hpp"

namespace MCEngine
{

class Camera : public Object
{
public:
    Camera(glm::vec3 position = glm::vec3(0.0f), glm::vec3 rotation = glm::vec3(0.0f));
    virtual ~Camera() override = default;

    glm::mat4 GetView() const { return m_View; }
    glm::mat4 GetProjection() const { return m_Projection; }

    void SetPosition(const glm::vec3 &position) override;
    void SetRotation(const glm::vec3 &rotation) override;

public:
    virtual void Update(float deltaTime) override = 0;

protected:
    glm::mat4 m_View;
    glm::mat4 m_Projection;

protected:
    void UpdateViewMatrix();
    virtual void UpdateProjectionMatrix() = 0;
};

} // namespace MCEngine