#pragma once

#include "ECS/Entity/EntityFactory.hpp"

namespace MCEngine
{

class Scene
{
public:
    Scene();
    virtual ~Scene();

    // Getters
    entt::registry &GetRegistry() { return m_Registry; }
    entt::entity GetMainCamera() const { return m_MainCamera; }

public:
    // Main loop
    void OnEvent(Event &event) {}
    void Update(float deltaTime);
    virtual void Render(CameraComponent &camera) const;
    virtual void RenderShadowMap() const = 0;

    void Resize(float width, float height);

protected:
    entt::registry m_Registry = {};

    // Camera control
    entt::entity m_MainCamera;
    entt::entity m_Camera2D;
    entt::entity m_Camera3D;

    // Shadow
    std::unique_ptr<MCEngine::FrameBuffer> m_ShadowMapPtr;
};

} // namespace MCEngine