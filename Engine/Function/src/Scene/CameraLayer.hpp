#pragma once

#include "Object/Camera/OrthoCamera.hpp"

namespace MCEngine
{

class CameraLayer : public Layer
{

public:
    CameraLayer();
    virtual ~CameraLayer() = default;

    void OnEvent(Event &event) override;
    void OnUpdate() override;

private:
    std::shared_ptr<OrthoCamera> m_Camera;
    float m_CameraMoveSpeed = 0.1f;
};

} // namespace MCEngine