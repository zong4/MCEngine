#pragma once

#include "ECS/Component/Component.hpp"

namespace MCEngine
{

class LightComponent : public Component
{
public:
    LightComponent(const glm::vec4 &color = glm::vec4(1.0f), float intensity = 1.0f, float range = 10.0f,
                   float spotAngle = 45.0f);

    const glm::vec4 &GetColor() const { return m_Color; }
    float GetIntensity() const { return m_Intensity; }
    float GetRange() const { return m_Range; }
    float GetSpotAngle() const { return m_SpotAngle; }

    void SetColor(const glm::vec4 &color) { m_Color = color; }
    void SetIntensity(float intensity) { m_Intensity = intensity; }
    void SetRange(float range) { m_Range = range; }
    void SetSpotAngle(float spotAngle) { m_SpotAngle = spotAngle; }

    void Update(float deltaTime) override {}

private:
    glm::vec4 m_Color;
    float m_Intensity;
    float m_Range;
    float m_SpotAngle; // For spot lights
};

} // namespace MCEngine