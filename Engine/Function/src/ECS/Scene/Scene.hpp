#pragma once

#include "Camera/Camera.hpp"
#include "ECS/Component/BasicComponent.hpp"
#include "ECS/Component/RendererComponent.hpp"

namespace MCEngine
{

class Scene
{
public:
    Scene() = default;
    virtual ~Scene() = default;

public:
    virtual void OnEvent(Event &event) = 0;
    virtual void Update(float deltaTime) = 0;
    virtual void Render(std::shared_ptr<Camera> camera) const = 0;

protected:
    // entt::entity m_CameraEntity;
    entt::registry m_Registry = {};
};

} // namespace MCEngine