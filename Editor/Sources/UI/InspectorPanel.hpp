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
};
} // namespace MCEditor