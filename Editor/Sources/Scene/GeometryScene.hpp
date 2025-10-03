#pragma once

#include <Function.hpp>

namespace MCEditor
{

class GeometryScene : public MCEngine::Scene
{
public:
    GeometryScene();
    virtual ~GeometryScene() override = default;

private:
    std::vector<glm::mat4> m_Offsets;
    float m_Magnitude = 0.1f;

protected:
    void RenderReally() const override;
};

} // namespace MCEditor