#pragma once

#include <Function.hpp>

namespace MCEditor
{

class SampleScene : public MCEngine::Scene
{
public:
    SampleScene();
    virtual ~SampleScene() override = default;

public:
    void Render(MCEngine::CameraComponent &camera) const override;
};

} // namespace MCEditor