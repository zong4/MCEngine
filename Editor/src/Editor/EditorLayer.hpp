#pragma once

#include <Function.hpp>

namespace MCEngine
{

class EditorLayer : public Layer
{

public:
    EditorLayer();
    virtual ~EditorLayer() = default;

    void OnAttach() override {}
    void OnDetach() override {}

    void OnEvent(Event &event) override;
    void OnUpdate(float deltaTime) override;
    void OnRender() override;
    void OnImGuiRender(float deltaTime) override {}

private:
    std::shared_ptr<Camera> m_Camera;
    std::shared_ptr<OrthoCamera> m_OrthoCamera;
    std::shared_ptr<PerspectiveCamera> m_PerspectiveCamera;

    float m_CameraMoveSpeed = 1.0f;
    float m_CameraRotateSpeed = 15.0f;

    Scene m_Scene;
};

} // namespace MCEngine