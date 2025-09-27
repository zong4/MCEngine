#pragma once

#include "Scene.hpp"

namespace MCEngine
{

class Scene2D : public Scene
{
public:
    Scene2D();
    virtual ~Scene2D() override = default;

public:
    virtual void OnEvent(Event &event) override {}
    virtual void Update(float deltaTime) override { Scene::Update(deltaTime); }
};

} // namespace MCEngine