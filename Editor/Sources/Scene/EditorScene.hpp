#pragma once

#include <Function.hpp>

namespace MCEditor
{

class EditorScene : public MCEngine::Scene
{
public:
    EditorScene();
    virtual ~EditorScene() override = default;

protected:
    void RenderShadowMapReally() const override {}
    void RenderReally() const override {}
};

} // namespace MCEditor