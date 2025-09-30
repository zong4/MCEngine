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
    void Render(CameraComponent *camera) const;
    void Render(CameraComponent &camera) const;
    void Render(const CameraComponent &camera) const;

    void Resize(float width, float height);

protected:
    entt::registry m_Registry = {};

    // Camera control
    entt::entity m_MainCamera;
    entt::entity m_Camera2D;
    entt::entity m_Camera3D;

private:
    void RenderAll(glm::mat4 viewMatrix, glm::mat4 projectionMatrix, glm::vec3 cameraPosition) const;
};

} // namespace MCEngine