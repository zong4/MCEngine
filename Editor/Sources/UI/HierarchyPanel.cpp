#include "HierarchyPanel.hpp"

#include <imgui.h>

void MCEditor::HierarchyPanel::OnImGuiRender(std::shared_ptr<MCEngine::Scene> scene, MCEngine::Entity &selectedEntity)
{
    ENGINE_PROFILE_FUNCTION();

    ImGui::Begin("Hierarchy");

    auto &&view = scene->GetRegistry().view<MCEngine::TagComponent, MCEngine::RelationshipComponent>();
    for (auto &&entity : view)
    {
        auto &&rel = view.get<MCEngine::RelationshipComponent>(entity);
        if (!rel.GetParent())
        {
            DrawEntityNode({entity, &scene->GetRegistry()}, selectedEntity);
        }
    }

    ImGui::End();
}

void MCEditor::HierarchyPanel::DrawEntityNode(MCEngine::Entity entity, MCEngine::Entity &selectedEntity)
{
    ENGINE_PROFILE_FUNCTION();

    ImGui::PushID((int)(uint32_t)entity);

    ImGuiTreeNodeFlags node_flags = ImGuiTreeNodeFlags_SpanAvailWidth;
    auto &&children = entity.GetComponent<MCEngine::RelationshipComponent>().GetChildren();
    if (children.empty())
        node_flags |= ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_Bullet;
    else
        node_flags |= ImGuiTreeNodeFlags_OpenOnArrow;

    bool opened = ImGui::TreeNodeEx(entity.GetComponent<MCEngine::TagComponent>().GetTag().c_str(), node_flags);
    if (ImGui::IsItemClicked())
        selectedEntity = entity;

    if (opened)
    {
        for (auto &&child : children)
            DrawEntityNode(child, selectedEntity);
        ImGui::TreePop();
    }

    ImGui::PopID();
}