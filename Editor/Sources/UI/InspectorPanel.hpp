#pragma once

#include <Function.hpp>

namespace MCEditor
{
class InspectorPanel
{
public:
    InspectorPanel() = default;
    ~InspectorPanel() = default;

    void OnImGuiRender(entt::registry &registry, entt::entity m_SelectedEntity) const;

protected:
    void DrawVec3Control(const std::string &label, glm::vec3 &values, float resetValue = 0.0f,
                         float columnWidth = 100.0f) const;
    void DrawAddComponentButton(entt::registry &registry, entt::entity m_SelectedEntity) const;
};
} // namespace MCEditor