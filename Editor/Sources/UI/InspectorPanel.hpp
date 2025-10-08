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
    static void DrawVec3Control(const std::string &label, const glm::vec3 &values,
                                std::function<void(const glm::vec3 &)> callback, float resetValue);
    static void DrawAddComponentButton(MCEngine::Entity selectedEntity);
};
} // namespace MCEditor