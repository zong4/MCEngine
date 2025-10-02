#pragma once

#include "ECS/Component/Basic/BasicComponent.hpp"

namespace MCEngine
{

enum class CameraType
{
    Ortho,
    Perspective
};

class CameraComponent : public Component
{
public:
    CameraComponent(const glm::vec3 &size);
    CameraComponent(float fov, float aspectRatio, float nearClip, float farClip);
    virtual ~CameraComponent() override;

    // Getters
    CameraType GetType() const { return m_Type; }
    const glm::mat4 &GetProjectionMatrix() const { return m_ProjectionMatrix; }
    const glm::vec3 &GetSize() const { return m_Size; }
    float GetFOV() const { return m_FOV; }
    float GetAspectRatio() const { return m_AspectRatio; }
    float GetNearClip() const { return m_NearClip; }
    float GetFarClip() const { return m_FarClip; }

    // Setters
    void SetFOV(float fov);
    void SetNearClip(float nearClip);
    void SetFarClip(float farClip);

public:
    virtual void Update(float deltaTime) override;
    void Resize(float width, float height);

private:
    CameraType m_Type;
    glm::mat4 m_ProjectionMatrix;
    glm::vec3 m_Size;
    float m_FOV, m_AspectRatio, m_NearClip, m_FarClip;

private:
    void UpdateViewMatrix();
    void UpdateProjectionMatrix();
};

} // namespace MCEngine