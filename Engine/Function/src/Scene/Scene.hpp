#pragma once

#include "ECS/Entity/EntityFactory.hpp"

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
    void Render2D() const;
    void Render3D() const;

protected:
    entt::registry m_Registry = {};

    // Camera control
    entt::entity m_Camera;
    entt::entity m_Camera2D;
    entt::entity m_Camera3D;
    float m_CameraMoveSpeed = 1.0f;
    float m_CameraRotateSpeed = 15.0f;
};

} // namespace MCEngine