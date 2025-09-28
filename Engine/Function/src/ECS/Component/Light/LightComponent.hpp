#pragma once

#include "ECS/Component/Component.hpp"

namespace MCEngine
{

class LightComponent : public Component
{
public:
    LightComponent(const glm::vec4 &color = glm::vec4(1.0f), float intensity = 1.0f);

    glm::vec4 &GetColor() { return m_Color; }
    const glm::vec4 &GetColor() const { return m_Color; }
    float &GetIntensity() { return m_Intensity; }
    float GetIntensity() const { return m_Intensity; }

    void SetColor(const glm::vec4 &color) { m_Color = color; }
    void SetIntensity(float intensity) { m_Intensity = intensity; }

    virtual void Update(float deltaTime) override {}

private:
    glm::vec4 m_Color;
    float m_Intensity;
};

} // namespace MCEngine