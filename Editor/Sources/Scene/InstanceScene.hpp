#pragma once

#include <Function.hpp>

namespace MCEditor
{

class InstanceScene : public MCEngine::Scene
{
public:
    InstanceScene();
    virtual ~InstanceScene() override = default;

public:
    void Render(MCEngine::CameraComponent &camera) const override;
    void RenderShadowMap() const override {}

private:
    std::vector<glm::mat4> m_Offsets;
};

} // namespace MCEditor