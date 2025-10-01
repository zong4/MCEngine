#pragma once

#include <Function.hpp>

namespace MCEditor
{

class FullScene : public MCEngine::Scene
{
public:
    FullScene();
    virtual ~FullScene() override = default;

private:
    entt::entity m_Light;

protected:
    void RenderShadowMapReally() const override;
    void RenderReally(MCEngine::CameraComponent &camera) const override;
};

} // namespace MCEditor