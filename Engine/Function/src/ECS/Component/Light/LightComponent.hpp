#pragma once

#include "ECS/Component/Component.hpp"

namespace MCEngine
{

struct LightComponent : public Component
{
    glm::vec4 Color;
    float Intensity;
    float Range;
    float SpotAngle; // For spot lights

public:
    LightComponent(glm::vec4 color = glm::vec4(1.0f), float intensity = 1.0f, float range = 10.0f,
                   float spotAngle = 45.0f)
        : Color(color), Intensity(intensity), Range(range), SpotAngle(spotAngle)
    {
    }
};

} // namespace MCEngine