#include "LightComponent.hpp"

MCEngine::LightComponent::LightComponent(const glm::vec4 &color, float intensity, float range, float spotAngle)
    : m_Color(color), m_Intensity(intensity), m_Range(range), m_SpotAngle(spotAngle)
{
    LOG_ENGINE_INFO("Light Component created with Color: " + ToString(m_Color) +
                    ", Intensity: " + std::to_string(m_Intensity) + ", Range: " + std::to_string(m_Range) +
                    ", Spot Angle: " + std::to_string(m_SpotAngle));
}