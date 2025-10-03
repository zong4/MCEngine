#pragma once

#include <Function.hpp>

namespace MCEditor
{

class InstanceScene : public MCEngine::Scene
{
public:
    InstanceScene();
    virtual ~InstanceScene() override = default;

private:
    std::vector<glm::mat4> m_Offsets;

protected:
    void RenderReally() const override;
};

} // namespace MCEditor