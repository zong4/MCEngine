#pragma once

#include "Camera/Camera.hpp"

namespace MCEngine
{

struct SpriteRendererComponent
{
    std::shared_ptr<VertexArray> VAOPtr;

    // Color tint
    glm::vec4 Color;
    std::shared_ptr<Texture> TexturePtr;

public:
    SpriteRendererComponent(std::shared_ptr<VertexArray> vaoPtr, glm::vec4 color = glm::vec4(1.0f),
                            std::shared_ptr<Texture> texturePtr = Texture::GetWhiteTexturePtr())
        : VAOPtr(vaoPtr), Color(color), TexturePtr(texturePtr)
    {
    }
};

struct MeshRendererComponent
{
    std::shared_ptr<VertexArray> VAOPtr;

    // Color tint
    glm::vec4 Color;

public:
    MeshRendererComponent(std::shared_ptr<VertexArray> vaoPtr, glm::vec4 color = glm::vec4(1.0f))
        : VAOPtr(vaoPtr), Color(color)
    {
    }
};

struct CameraComponent
{
    std::shared_ptr<Camera> CameraPtr;

public:
    CameraComponent(std::shared_ptr<Camera> camera) : CameraPtr(camera) {}
};

// todo
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