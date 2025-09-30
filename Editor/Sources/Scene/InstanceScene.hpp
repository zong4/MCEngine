#pragma once

#include <Function.hpp>

namespace MCEditor
{

class InstanceScene : public MCEngine::Scene
{
public:
    InstanceScene();
    virtual ~InstanceScene() override = default;

    void Render(MCEngine::CameraComponent &camera) const override;

private:
    std::vector<glm::mat4> m_Offsets;
};

} // namespace MCEditor