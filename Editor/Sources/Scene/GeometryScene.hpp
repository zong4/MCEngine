#pragma once

#include <Function.hpp>

namespace MCEditor
{

class GeometryScene : public MCEngine::Scene
{
public:
    GeometryScene();
    virtual ~GeometryScene() override = default;

public:
    void Render(MCEngine::CameraComponent &camera) const override;
    void RenderShadowMap() const override {}

private:
    std::vector<glm::mat4> m_Offsets;
    float m_Magnitude = 0.1f;
};

} // namespace MCEditor