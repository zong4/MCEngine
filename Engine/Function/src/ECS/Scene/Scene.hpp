#pragma once

#include "ECS/Component/Basic/BasicComponent.hpp"
#include "ECS/Component/Camera/CameraComponent.hpp"
#include "ECS/Component/Light/LightComponent.hpp"
#include "ECS/Component/Renderer/RendererComponent.hpp"

namespace MCEngine
{

class Scene
{
public:
    Scene();
    ~Scene();

    entt::registry &GetRegistry() { return m_Registry; }

public:
    void OnEvent(Event &event) {}
    void Update(float deltaTime);
    void Render() const;

protected:
    entt::registry m_Registry = {};

    // Camera control
    entt::entity m_Camera;
    entt::entity m_Camera2D;
    entt::entity m_Camera3D;
    TransformComponent *m_CameraTransformComponent = nullptr;
    CameraComponent *m_CameraComponent = nullptr;
    float m_CameraMoveSpeed = 1.0f;
    float m_CameraRotateSpeed = 15.0f;

    entt::entity m_Light;

protected:
    void UpdateCamera(const glm::vec3 &position, const glm::vec3 &rotation);
};

} // namespace MCEngine