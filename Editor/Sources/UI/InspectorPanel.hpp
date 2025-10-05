#pragma once

#include <Function.hpp>

namespace MCEditor
{
class InspectorPanel
{
public:
    InspectorPanel() = default;
    ~InspectorPanel() = default;

    void OnImGuiRender() const;

protected:
    static void DrawVec3Control(const std::string &label, glm::vec3 &values, float resetValue);
    static void DrawAddComponentButton(MCEngine::Entity selectedEntity);
};
} // namespace MCEditor