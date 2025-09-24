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
    float m_CameraMoveSpeed = 0.1f;
    std::shared_ptr<OrthoCamera> m_Camera;

    std::vector<std::shared_ptr<Object>> m_Objects;
};

} // namespace MCEngine