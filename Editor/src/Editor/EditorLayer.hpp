#pragma once

#include <Function.hpp>

namespace MCEngine
{

class EditorLayer : public Layer
{

public:
    EditorLayer(std::shared_ptr<Camera> sceneCameraPtr, std::shared_ptr<Camera> gameCameraPtr);
    virtual ~EditorLayer() = default;

    void OnAttach() override {}
    void OnDetach() override {}

    void SetSceneCameraPtr(const std::shared_ptr<Camera> &camera) { m_SceneCameraPtr = camera; }
    void SetGameCameraPtr(const std::shared_ptr<Camera> &camera) { m_GameCameraPtr = camera; }

public:
    void OnEvent(Event &event) override;
    void OnUpdate(float deltaTime) override;
    void OnRender() override;
    void OnImGuiRender(float deltaTime) override {}

private:
    std::shared_ptr<Camera> m_CameraPtr;
    std::shared_ptr<Camera> m_SceneCameraPtr;
    std::shared_ptr<Camera> m_GameCameraPtr;
    float m_CameraMoveSpeed = 1.0f;
    float m_CameraRotateSpeed = 15.0f;

    Scene2D m_Scene2D;
    Scene3D m_Scene3D;
};

} // namespace MCEngine