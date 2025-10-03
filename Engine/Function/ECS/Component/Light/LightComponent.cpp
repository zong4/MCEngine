#include "LightComponent.hpp"

MCEngine::LightComponent::LightComponent(LightType type, const glm::vec3 &color, float intensity, float constant,
                                         float linear, float quadratic, float cutOff, float outerCutOff)
    : m_Type(type), m_Color(color), m_Intensity(intensity), m_Constant(constant), m_Linear(linear),
      m_Quadratic(quadratic), m_CutOff(cutOff), m_OuterCutOff(outerCutOff)
{
    LOG_ENGINE_INFO("Light Component created with Color: " + ToString(m_Color) +
                    ", Intensity: " + std::to_string(m_Intensity) + ", Constant: " + std::to_string(m_Constant) +
                    ", Linear: " + std::to_string(m_Linear) + ", Quadratic: " + std::to_string(m_Quadratic) +
                    ", CutOff: " + std::to_string(m_CutOff) + ", OuterCutOff: " + std::to_string(m_OuterCutOff));
}

void MCEngine::LightComponent::SetAttenuation(float constant, float linear, float quadratic)
{
    if (m_Type == LightType::Directional)
    {
        LOG_ENGINE_WARN("Trying to set attenuation on a directional light");
        return;
    }
    m_Constant = constant;
    m_Linear = linear;
    m_Quadratic = quadratic;
}

void MCEngine::LightComponent::SetCutOff(float cutOff, float outerCutOff)
{
    if (m_Type != LightType::Spot)
    {
        LOG_ENGINE_WARN("Trying to set cutOff on a non-spot light");
        return;
    }
    m_CutOff = cutOff;
    m_OuterCutOff = outerCutOff;
}
