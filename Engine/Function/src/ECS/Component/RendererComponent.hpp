#pragma once

#include "Camera/Camera.hpp"

namespace MCEngine
{

struct SpriteRendererComponent
{
    std::shared_ptr<VertexArray> VAOPtr;
    glm::vec4 Color;

public:
    SpriteRendererComponent(std::shared_ptr<VertexArray> vao, glm::vec4 color = glm::vec4(1.0f))
        : VAOPtr(vao), Color(color)
    {
    }
};

struct MeshRendererComponent
{
    std::shared_ptr<VertexArray> VAOPtr;
    glm::vec4 Color;

public:
    MeshRendererComponent(std::shared_ptr<VertexArray> vao, glm::vec4 color = glm::vec4(1.0f))
        : VAOPtr(vao), Color(color)
    {
    }
};

struct CameraComponent
{
    std::shared_ptr<Camera> CameraPtr;

public:
    CameraComponent(std::shared_ptr<Camera> camera) : CameraPtr(camera) {}
};

struct LightComponent
{
    glm::vec3 Color;
    float Intensity;
    float Range;
    float SpotAngle; // For spot lights
public:
    LightComponent(glm::vec3 color = glm::vec3(1.0f), float intensity = 1.0f, float range = 10.0f,
                   float spotAngle = 45.0f)
        : Color(color), Intensity(intensity), Range(range), SpotAngle(spotAngle)
    {
    }
};

} // namespace MCEngine