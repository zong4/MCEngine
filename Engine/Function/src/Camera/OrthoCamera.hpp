#pragma once

#include "Camera.hpp"

namespace MCEngine
{

class OrthoCamera : public Camera
{
public:
    OrthoCamera(glm::vec3 size, glm::vec3 position = glm::vec3(0.0f), glm::vec3 rotation = glm::vec3(0.0f));
    virtual ~OrthoCamera() override = default;

    glm::vec3 GetSize() const { return m_Size; }
    void SetSize(const glm::vec3 &size);

public:
    void OnEvent(Event &event) override;
    void Update(float deltaTime) override {}

private:
    glm::vec3 m_Size;

protected:
    void UpdateProjectionMatrix() override;
};

} // namespace MCEngine