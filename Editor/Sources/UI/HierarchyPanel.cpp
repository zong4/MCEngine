#include "HierarchyPanel.hpp"

#include "Manager/SceneManager.hpp"
#include <imgui.h>

void MCEditor::HierarchyPanel::OnImGuiRender()
{
    ENGINE_PROFILE_FUNCTION();

    ImGui::Begin("Hierarchy");

    auto &&registry = SceneManager::GetInstance().GetActiveScene()->GetRegistry();
    for (auto &&entity : registry.view<MCEngine::RelationshipComponent>())
    {
        if (!registry.get<MCEngine::RelationshipComponent>(entity).GetParent())
            DrawEntityNode({entity, &registry});
    }

    ImGui::End();
}

void MCEditor::HierarchyPanel::DrawEntityNode(MCEngine::Entity entity)
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
        SceneManager::GetInstance().SetSelectedEntity(entity);

    if (opened)
    {
        for (auto &&child : children)
            DrawEntityNode(child);
        ImGui::TreePop();
    }

    ImGui::PopID();
}