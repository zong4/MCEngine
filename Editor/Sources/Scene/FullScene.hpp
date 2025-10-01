#pragma once

#include <Function.hpp>

namespace MCEditor
{

class FullScene : public MCEngine::Scene
{
public:
    FullScene();
    virtual ~FullScene() override = default;

public:
    void Render(MCEngine::CameraComponent &camera) const override;
    void RenderShadowMap() const override;

private:
    entt::entity m_Light;
};

} // namespace MCEditor