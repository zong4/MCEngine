#pragma once

#include "Scene.hpp"

namespace MCEngine
{

class Scene3D : public Scene
{
public:
    Scene3D();
    virtual ~Scene3D() override = default;

public:
    virtual void OnEvent(Event &event) override {}
    virtual void Update(float deltaTime) override { Scene::Update(deltaTime); }
};

} // namespace MCEngine