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
    CameraComponent(TransformComponent *transformComponent, const glm::vec3 &size);
    CameraComponent(TransformComponent *transformComponent, float fov, float aspectRatio, float nearClip,
                    float farClip);
    virtual ~CameraComponent() override;

    CameraType GetType() const { return m_Type; }
    TransformComponent *GetTransformComponent() const { return m_TransformComponent; }
    const glm::mat4 &GetViewMatrix() const { return m_ViewMatrix; }
    const glm::mat4 &GetProjectionMatrix() const { return m_ProjectionMatrix; }
    const glm::vec3 &GetSize() const { return m_Size; }
    float GetFOV() const { return m_FOV; }
    float GetAspectRatio() const { return m_AspectRatio; }
    float GetNearClip() const { return m_NearClip; }
    float GetFarClip() const { return m_FarClip; }

    void SetSize(const glm::vec3 &size);
    void SetFOV(float fov);
    void SetAspectRatio(float aspectRatio);
    void SetNearClip(float nearClip);
    void SetFarClip(float farClip);

    virtual void Update(float deltaTime) override;

private:
    CameraType m_Type;

    TransformComponent *m_TransformComponent = nullptr;
    glm::mat4 m_ViewMatrix;
    glm::mat4 m_ProjectionMatrix;

    glm::vec3 m_Size;
    float m_FOV, m_AspectRatio, m_NearClip, m_FarClip;

private:
    void UpdateViewMatrix();
    void UpdateProjectionMatrix();
};

} // namespace MCEngine