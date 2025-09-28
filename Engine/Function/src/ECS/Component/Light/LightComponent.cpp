#include "LightComponent.hpp"

MCEngine::LightComponent::LightComponent(const glm::vec4 &color, float intensity)
    : m_Color(color), m_Intensity(intensity)
{
    LOG_ENGINE_INFO("Light Component created with Color: " + ToString(m_Color) +
                    ", Intensity: " + std::to_string(m_Intensity));
}