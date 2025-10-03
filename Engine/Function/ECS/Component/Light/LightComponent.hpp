#pragma once

#include "pch.hpp"

namespace MCEngine
{

enum class LightType
{
    Directional,
    Point,
    Spot
};

class LightComponent
{
public:
    LightComponent(LightType type, const glm::vec3 &color = glm::vec3(1.0f), float intensity = 1.0f,
                   float constant = 1.0f, float linear = 0.09f, float quadratic = 0.032f, float innerAngle = 12.5f,
                   float outerAngle = 15.0f);

    // Getters
    LightType GetType() const { return m_Type; }
    glm::vec3 &GetColor() { return m_Color; }
    float &GetIntensity() { return m_Intensity; }
    float &GetConstant() { return m_Constant; }
    float &GetLinear() { return m_Linear; }
    float &GetQuadratic() { return m_Quadratic; }
    float &GetInnerAngle() { return m_InnerAngle; }
    float &GetOuterAngle() { return m_OuterAngle; }
    const glm::vec3 &GetColor() const { return m_Color; }
    float GetIntensity() const { return m_Intensity; }
    float GetConstant() const { return m_Constant; }
    float GetLinear() const { return m_Linear; }
    float GetQuadratic() const { return m_Quadratic; }
    float GetInnerAngle() const { return m_InnerAngle; }
    float GetOuterAngle() const { return m_OuterAngle; }

    // Setters
    void SetColor(const glm::vec3 &color) { m_Color = color; }
    void SetIntensity(float intensity) { m_Intensity = intensity; }
    void SetAttenuation(float constant, float linear, float quadratic);
    void SetAngles(float innerAngle, float outerAngle);

private:
    LightType m_Type;
    glm::vec3 m_Color;
    float m_Intensity;
    float m_Constant, m_Linear, m_Quadratic;
    float m_InnerAngle, m_OuterAngle;
};

} // namespace MCEngine