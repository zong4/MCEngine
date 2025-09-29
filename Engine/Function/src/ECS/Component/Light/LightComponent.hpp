#pragma once

#include "ECS/Component/Component.hpp"

namespace MCEngine
{

enum class LightType
{
    Directional,
    Point,
    Spot
};

class LightComponent : public Component
{
public:
    LightComponent(const glm::vec3 &color, float intensity);
    LightComponent(const glm::vec3 &color, float intensity, float constant, float linear, float quadratic);
    LightComponent(const glm::vec3 &color, float intensity, float constant, float linear, float quadratic, float cutOff,
                   float outerCutOff);

    LightType GetType() const { return m_LightType; }
    glm::vec3 &GetColor() { return m_Color; }
    const glm::vec3 &GetColor() const { return m_Color; }
    float &GetIntensity() { return m_Intensity; }
    float GetIntensity() const { return m_Intensity; }
    float &GetConstant() { return m_Constant; }
    float GetConstant() const { return m_Constant; }
    float &GetLinear() { return m_Linear; }
    float GetLinear() const { return m_Linear; }
    float &GetQuadratic() { return m_Quadratic; }
    float GetQuadratic() const { return m_Quadratic; }
    float &GetCutOff() { return m_CutOff; }
    float GetCutOff() const { return m_CutOff; }
    float &GetOuterCutOff() { return m_OuterCutOff; }
    float GetOuterCutOff() const { return m_OuterCutOff; }

    void SetColor(const glm::vec4 &color) { m_Color = color; }
    void SetIntensity(float intensity) { m_Intensity = intensity; }
    void SetAttenuation(float constant, float linear, float quadratic);
    void SetCutOff(float cutOff, float outerCutOff);

    virtual void Update(float deltaTime) override {}

private:
    LightType m_LightType;
    glm::vec3 m_Color;
    float m_Intensity;
    float m_Constant, m_Linear, m_Quadratic;
    float m_CutOff, m_OuterCutOff;
};

} // namespace MCEngine