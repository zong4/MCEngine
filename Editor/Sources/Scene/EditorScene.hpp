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
    void RenderReally() const override {}
};

} // namespace MCEditor