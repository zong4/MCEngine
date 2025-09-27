#pragma once

#include "ECS/Component/Basic/TransformComponent.hpp"
#include "ECS/Component/Camera/CameraComponent.hpp"
#include "ECS/Component/Light/LightComponent.hpp"
#include "ECS/Component/Renderer/RendererComponent.hpp"

namespace MCEngine
{

class Scene
{
public:
    Scene();
    virtual ~Scene() = default;

    entt::registry &GetRegistry() { return m_Registry; }

public:
    virtual void OnEvent(Event &event) = 0;
    virtual void Update(float deltaTime) = 0;
    void Render() const;

protected:
    entt::registry m_Registry = {};

    // Camera control
    entt::entity m_Camera;
    float m_CameraMoveSpeed = 1.0f;
    float m_CameraRotateSpeed = 15.0f;

    entt::entity m_Light;

protected:
    void UpdateCamera(glm::vec3 position, glm::vec3 rotation);
};

} // namespace MCEngine