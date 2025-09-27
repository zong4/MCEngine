#pragma once

#include "Scene.hpp"

namespace MCEngine
{

class Scene3D : public Scene
{
public:
    Scene3D() = default;
    ~Scene3D() override = default;

public:
    void OnEvent(Event &event) override {}
    void Update(float deltaTime) override {}
    void Render(std::shared_ptr<Camera> camera) const override;

    entt::entity AddCube(TransformComponent transform, MeshRendererComponent mesh);
};

} // namespace MCEngine