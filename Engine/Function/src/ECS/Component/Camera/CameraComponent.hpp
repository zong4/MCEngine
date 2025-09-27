#pragma once

#include "ECS/Component/Component.hpp"

namespace MCEngine
{

struct CameraComponent : public Component
{
    glm::mat4 ViewMatrix;
    glm::mat4 ProjectionMatrix;

public:
    void UpdateViewMatrix(glm::vec3 position, glm::vec3 rotation);
    virtual void UpdateProjectionMatrix() {}
};

struct OrthoCameraComponent : public CameraComponent
{
    glm::vec3 Size;

public:
    OrthoCameraComponent(const glm::vec3 &size) : Size(size) { UpdateProjectionMatrix(); }

    virtual void UpdateProjectionMatrix() override
    {
        ProjectionMatrix =
            glm::ortho(-Size.x / 2.0f, Size.x / 2.0f, -Size.y / 2.0f, Size.y / 2.0f, -Size.z / 2.0f, Size.z / 2.0f);
    }
};

struct PerspectiveCameraComponent : public CameraComponent
{
    float FOV;
    float AspectRatio;
    float NearClip;
    float FarClip;

public:
    PerspectiveCameraComponent(float fov, float aspectRatio, float nearClip, float farClip)
        : FOV(fov), AspectRatio(aspectRatio), NearClip(nearClip), FarClip(farClip)
    {
        UpdateProjectionMatrix();
    }

    virtual void UpdateProjectionMatrix() override
    {
        ProjectionMatrix = glm::perspective(glm::radians(FOV), AspectRatio, NearClip, FarClip);
    }
};

} // namespace MCEngine