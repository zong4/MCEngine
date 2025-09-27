#pragma once

#include "Scene.hpp"

namespace MCEngine
{

class Scene3D : public Scene
{
public:
    Scene3D();
    virtual ~Scene3D() override = default;

    void SetLight(const entt::entity &light) { m_Light = light; }

public:
    virtual void OnEvent(Event &event) override {}
    virtual void Update(float deltaTime) override {}
    virtual void Render() const override;

private:
    entt::entity m_Light;
};

} // namespace MCEngine