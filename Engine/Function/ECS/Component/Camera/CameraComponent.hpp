#pragma once

#include "pch.hpp"

namespace MCEngine
{

enum class CameraType
{
    Orthographic,
    Perspective
};

class CameraComponent
{
public:
    CameraComponent(CameraType type, float width = 1600.0f, float height = 900.0f, float fov = 45.0f,
                    float nearClip = 0.1f, float farClip = 100.0f);

    // Getters
    CameraType GetType() const { return m_Type; }
    float GetWidth() const { return m_Width; }
    float GetHeight() const { return m_Height; }
    float GetScale() const { return m_Scale; }
    float GetFOV() const { return m_FOV; }
    float GetNearClip() const { return m_NearClip; }
    float GetFarClip() const { return m_FarClip; }
    const glm::mat4 &GetProjectionMatrix() const { return m_ProjectionMatrix; }

    // Setters
    void SetType(CameraType type);
    void SetScale(float scale);
    void SetFOV(float fov);
    void SetNearClip(float nearClip);
    void SetFarClip(float farClip);

public:
    void Resize(float width, float height);

private:
    CameraType m_Type;
    float m_Width, m_Height, m_Scale = 1.0f;
    float m_FOV, m_NearClip, m_FarClip;
    glm::mat4 m_ProjectionMatrix;

private:
    void UpdateProjectionMatrix();
};

} // namespace MCEngine