#pragma once

#include "Scene.hpp"

namespace MCEngine
{

class Scene3D : public Scene
{
public:
    Scene3D();
    ~Scene3D() override = default;

    void SetLight(const entt::entity &light) { m_Light = light; }

public:
    void OnEvent(Event &event) override {}
    void Update(float deltaTime) override {}
    void Render(const std::shared_ptr<Camera> &camera) const override;

    entt::entity AddCube(TransformComponent transform, MeshRendererComponent mesh);

private:
    entt::entity m_Light;
};

} // namespace MCEngine