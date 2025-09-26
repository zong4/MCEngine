#pragma once

#include "Component.hpp"
#include "Object/Camera/Camera.hpp"

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

    entt::entity CreateEntity();

private:
    entt::registry m_Registry = {};
};

} // namespace MCEngine