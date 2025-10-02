#pragma once

#include "Entity.hpp"

namespace MCEngine
{

class ScriptableEntity : public Entity
{
public:
    ScriptableEntity(entt::entity handle, entt::registry *registry) : Entity(handle, registry) {}
    virtual ~ScriptableEntity() = default;

    virtual void OnCreate() {}
    virtual void OnUpdate(float deltaTime) {}
    virtual void OnDestroy() {}

    virtual void Resize(int width, int height) {}
};

} // namespace MCEngine