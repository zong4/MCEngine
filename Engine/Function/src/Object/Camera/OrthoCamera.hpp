#pragma once

#include "Camera.hpp"

namespace MCEngine
{

class OrthoCamera : public Camera
{
public:
    OrthoCamera(glm::vec3 position, glm::vec2 size);
    virtual ~OrthoCamera() override = default;

    glm::vec2 GetSize() const { return m_Size; }
    void SetSize(const glm::vec2 &size);

public:
    void OnEvent(Event &event) override;
    void Update(float deltaTime) override {}

private:
    glm::vec2 m_Size;

protected:
    void UpdateProjectionMatrix() override;
};

} // namespace MCEngine