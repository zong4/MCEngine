#pragma once

#include <Function.hpp>

namespace MCEditor
{

class SampleScene : public MCEngine::Scene
{
public:
    SampleScene();
    virtual ~SampleScene() override = default;

private:
    entt::entity m_Light;

protected:
    void RenderShadowMapReally() const override;
    void RenderReally(MCEngine::CameraComponent &camera) const override;
};

} // namespace MCEditor