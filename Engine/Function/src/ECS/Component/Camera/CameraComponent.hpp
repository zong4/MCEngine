#pragma once

#include "ECS/Component/Component.hpp"

namespace MCEngine
{

class CameraComponent : public Component
{
public:
    CameraComponent() = default;
    virtual ~CameraComponent() override = default;

    const glm::mat4 &GetViewMatrix() const { return m_ViewMatrix; }
    const glm::mat4 &GetProjectionMatrix() const { return m_ProjectionMatrix; }

    void UpdateViewMatrix(const glm::vec3 &position, const glm::vec3 &rotation);
    virtual void UpdateProjectionMatrix() = 0;

protected:
    glm::mat4 m_ViewMatrix;
    glm::mat4 m_ProjectionMatrix;
};

class OrthoCameraComponent : public CameraComponent
{

public:
    OrthoCameraComponent(const glm::vec3 &size);

    const glm::vec3 &GetSize() const { return m_Size; }
    void SetSize(const glm::vec3 &size);

    virtual void UpdateProjectionMatrix() override;

private:
    glm::vec3 m_Size;
};

class PerspectiveCameraComponent : public CameraComponent
{

public:
    PerspectiveCameraComponent(float fov, float aspectRatio, float nearClip, float farClip);

    float GetFOV() const { return m_FOV; }
    float GetAspectRatio() const { return m_AspectRatio; }
    float GetNearClip() const { return m_NearClip; }
    float GetFarClip() const { return m_FarClip; }

    void SetFOV(float fov);
    void SetAspectRatio(float aspectRatio);
    void SetNearClip(float nearClip);
    void SetFarClip(float farClip);

    virtual void UpdateProjectionMatrix() override;

private:
    float m_FOV;
    float m_AspectRatio;
    float m_NearClip;
    float m_FarClip;
};

} // namespace MCEngine