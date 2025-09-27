#pragma once

#include "Camera/Camera.hpp"
#include "Component.hpp"

namespace MCEngine
{

class Scene
{
public:
    Scene();
    ~Scene();

public:
    void OnEvent(Event &event) {}
    void Update(float deltaTime);
    void Render(std::shared_ptr<Camera> camera) const;

    entt::entity AddSquare(TransformComponent transform, SpriteRendererComponent sprite);
    entt::entity AddCube(TransformComponent transform, MeshRendererComponent mesh);

private:
    // entt::entity m_CameraEntity;
    entt::registry m_Registry = {};
};

} // namespace MCEngine