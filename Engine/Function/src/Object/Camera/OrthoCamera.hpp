#pragma once

#include "Object/Object.hpp"

namespace MCEngine
{

class OrthoCamera : public Object
{
public:
    OrthoCamera(glm::vec3 position, glm::vec2 size);
    virtual ~OrthoCamera() override = default;

    glm::vec2 GetSize() const { return m_Size; }
    glm::mat4 GetProjection() const { return m_Projection; }
    glm::mat4 GetView() const { return m_View; }

    void SetPosition(const glm::vec3 &position) override;
    void SetSize(const glm::vec2 &size);

public:
    void OnEvent(Event &event);
    void Update() override;

private:
    glm::vec2 m_Size;
    glm::mat4 m_Projection;
    glm::mat4 m_View;

private:
    void UpdateView();
};

} // namespace MCEngine