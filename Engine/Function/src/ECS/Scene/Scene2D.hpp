#pragma once

#include "Scene.hpp"

namespace MCEngine
{

class Scene2D : public Scene
{
public:
    Scene2D() = default;
    ~Scene2D() override = default;

public:
    void OnEvent(Event &event) override {}
    void Update(float deltaTime) override {}
    void Render(const std::shared_ptr<Camera> &camera) const override;

    entt::entity AddSquare(TransformComponent transform, SpriteRendererComponent sprite);
};

} // namespace MCEngine