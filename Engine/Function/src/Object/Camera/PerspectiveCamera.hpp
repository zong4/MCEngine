#pragma once

#include "Camera.hpp"

namespace MCEngine
{

class PerspectiveCamera : public Camera
{
public:
    PerspectiveCamera(glm::vec3 position, float fov, float aspectRatio, float nearClip, float farClip);
    virtual ~PerspectiveCamera() override = default;

    float GetFOV() const { return m_FOV; }
    float GetAspectRatio() const { return m_AspectRatio; }
    float GetNearClip() const { return m_NearClip; }
    float GetFarClip() const { return m_FarClip; }

    void SetFOV(float fov);
    void SetAspectRatio(float aspectRatio);
    void SetNearClip(float nearClip);
    void SetFarClip(float farClip);

public:
    void OnEvent(Event &event) override;
    void Update(float deltaTime) override {}

private:
    float m_FOV;
    float m_AspectRatio;
    float m_NearClip;
    float m_FarClip;

protected:
    void UpdateProjectionMatrix() override;
};

} // namespace MCEngine