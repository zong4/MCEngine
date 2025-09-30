#pragma once

#include "ECS/Entity/EntityFactory.hpp"

namespace MCEngine
{

class Scene
{
public:
    Scene();
    virtual ~Scene();

    entt::registry &GetRegistry() { return m_Registry; }
    entt::entity GetMainCamera() const { return m_MainCamera; }

public:
    void OnEvent(Event &event) {}
    void Update(float deltaTime);

    virtual void Render(CameraComponent &camera) const;

    void Resize(float width, float height);

protected:
    entt::registry m_Registry = {};

    // Camera control
    entt::entity m_MainCamera;
    entt::entity m_Camera2D;
    entt::entity m_Camera3D;
};

} // namespace MCEngine