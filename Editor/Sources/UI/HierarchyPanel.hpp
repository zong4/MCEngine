#pragma once

#include <Function.hpp>

namespace MCEditor
{

class HierarchyPanel
{
public:
    HierarchyPanel() = default;
    ~HierarchyPanel() = default;

    entt::entity GetSelectedEntity() const { return m_SelectedEntity; }

public:
    void OnImGuiRender(entt::registry &registry);

private:
    entt::entity m_SelectedEntity = entt::null;

private:
    void DrawEntityNode(entt::registry &registry, entt::entity entity);
};

} // namespace MCEditor