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
    LightComponent(const glm::vec3 &color, float intensity);
    LightComponent(const glm::vec3 &color, float intensity, float constant, float linear, float quadratic);
    LightComponent(const glm::vec3 &color, float intensity, float constant, float linear, float quadratic, float cutOff,
                   float outerCutOff);

    // Getters
    LightType GetType() const { return m_LightType; }
    glm::vec3 &GetColor() { return m_Color; }
    float &GetIntensity() { return m_Intensity; }
    float &GetConstant() { return m_Constant; }
    float &GetLinear() { return m_Linear; }
    float &GetQuadratic() { return m_Quadratic; }
    float &GetCutOff() { return m_CutOff; }
    float &GetOuterCutOff() { return m_OuterCutOff; }
    const glm::vec3 &GetColor() const { return m_Color; }
    float GetIntensity() const { return m_Intensity; }
    float GetConstant() const { return m_Constant; }
    float GetLinear() const { return m_Linear; }
    float GetQuadratic() const { return m_Quadratic; }
    float GetCutOff() const { return m_CutOff; }
    float GetOuterCutOff() const { return m_OuterCutOff; }

    // Setters
    void SetColor(const glm::vec4 &color) { m_Color = color; }
    void SetIntensity(float intensity) { m_Intensity = intensity; }
    void SetAttenuation(float constant, float linear, float quadratic);
    void SetCutOff(float cutOff, float outerCutOff);

private:
    LightType m_LightType;
    glm::vec3 m_Color;
    float m_Intensity;
    float m_Constant, m_Linear, m_Quadratic;
    float m_CutOff, m_OuterCutOff;
};

} // namespace MCEngine