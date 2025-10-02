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
    float m_CameraMoveSpeed = 5.0f;
    float m_CameraRotateSpeed = 45.0f;
};

} // namespace MCEditor