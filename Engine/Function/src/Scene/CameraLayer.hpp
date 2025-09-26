#pragma once

#include "Object/Camera/Camera.hpp"
#include "Object/Camera/OrthoCamera.hpp"
#include "Object/Camera/PerspectiveCamera.hpp"

namespace MCEngine
{

class CameraLayer : public Layer
{

public:
    CameraLayer();
    virtual ~CameraLayer() = default;

    void OnAttach() override {}
    void OnDetach() override {}

    void OnEvent(Event &event) override;
    void OnUpdate(float deltaTime) override;

private:
    std::shared_ptr<Camera> m_Camera;
    std::shared_ptr<OrthoCamera> m_OrthoCamera;
    std::shared_ptr<PerspectiveCamera> m_PerspectiveCamera;

    float m_CameraMoveSpeed = 1.0f;
    float m_CameraRotateSpeed = 10.0f;

    std::vector<std::shared_ptr<Object>> m_Objects;
};

} // namespace MCEngine