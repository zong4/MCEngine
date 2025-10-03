#include "HierarchyPanel.hpp"

#include <imgui.h>

void MCEditor::HierarchyPanel::OnImGuiRender(entt::registry &registry)
{
    ENGINE_PROFILE_FUNCTION();

    auto &&view = registry.view<MCEngine::TagComponent, MCEngine::RelationshipComponent>();
    for (auto &&entity : view)
    {
        auto &&rel = view.get<MCEngine::RelationshipComponent>(entity);
        if (!rel.GetParent())
        {
            DrawEntityNode(registry, entity);
        }
    }
}

void MCEditor::HierarchyPanel::DrawEntityNode(entt::registry &registry, entt::entity entity)
{
    ENGINE_PROFILE_FUNCTION();

    auto &&view = registry.view<MCEngine::TagComponent, MCEngine::RelationshipComponent>();

    auto &&children = view.get<MCEngine::RelationshipComponent>(entity).GetChildren();
    ImGuiTreeNodeFlags node_flags = ImGuiTreeNodeFlags_SpanAvailWidth;
    if (children.empty())
        node_flags |= ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_Bullet;
    else
        node_flags |= ImGuiTreeNodeFlags_OpenOnArrow;

    bool opened = ImGui::TreeNodeEx((void *)(uint64_t)(uint32_t)entity, node_flags,
                                    view.get<MCEngine::TagComponent>(entity).GetTag().c_str(), (uint32_t)entity);

    if (ImGui::IsItemClicked())
        m_SelectedEntity = entity;

    if (opened)
    {
        for (auto &&child : children)
            DrawEntityNode(registry, child);
        ImGui::TreePop();
    }
}