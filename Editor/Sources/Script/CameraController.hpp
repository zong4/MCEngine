#pragma once

#include <Function.hpp>

namespace MCEditor
{

class CameraController : public MCEngine::ScriptableEntity
{
public:
    CameraController() = default;
    virtual ~CameraController() override = default;

public:
    void OnStart() override;
    void OnUpdate(float deltaTime) override;

private:
    float m_MoveSpeed = 3.0f;
    float m_RotateSpeed = 30.0f;
    float m_ZoomSpeed = 2.0f;
};

} // namespace MCEditor