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
    MCEngine::Entity m_Light;

protected:
    void RenderShadowMapReally() const override;
    void RenderReally() const override;
};

} // namespace MCEditor