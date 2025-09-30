#pragma once

#include <Function.hpp>

namespace MCEditor
{

class GeometryScene : public MCEngine::Scene
{
public:
    GeometryScene();
    virtual ~GeometryScene() override = default;

    void Render(MCEngine::CameraComponent &camera) const override;

private:
    std::vector<glm::mat4> m_Offsets;
};

} // namespace MCEditor