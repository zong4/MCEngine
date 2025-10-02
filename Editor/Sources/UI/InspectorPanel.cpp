#include "InspectorPanel.hpp"

#include <imgui.h>

void MCEditor::InspectorPanel::OnImGuiRender(entt::registry &registry, entt::entity m_SelectedEntity) const
{
    ENGINE_PROFILE_FUNCTION();

    if (m_SelectedEntity != entt::null)
    {
        // TagComponent
        if (auto &&tag = registry.try_get<MCEngine::TagComponent>(m_SelectedEntity))
        {
            std::string header = "Tag Component##" + std::to_string(static_cast<uint32_t>(m_SelectedEntity));
            if (ImGui::CollapsingHeader(header.c_str(), ImGuiTreeNodeFlags_DefaultOpen))
            {
                char buffer[256];
                memset(buffer, 0, sizeof(buffer));
                strncpy(buffer, tag->GetTag().c_str(), sizeof(buffer));
                if (ImGui::InputText("Tag", buffer, sizeof(buffer)))
                    tag->SetTag(std::string(buffer));
            }
        }

        // TransformComponent
        if (auto &&transform = registry.try_get<MCEngine::TransformComponent>(m_SelectedEntity))
        {
            std::string header = "Transform Component##" + std::to_string(static_cast<uint32_t>(m_SelectedEntity));
            if (ImGui::CollapsingHeader(header.c_str(), ImGuiTreeNodeFlags_DefaultOpen))
            {
                ImGui::DragFloat3("Position", glm::value_ptr(transform->GetPosition()), 0.1f);
                ImGui::DragFloat3("Rotation", glm::value_ptr(transform->GetRotation()), 0.1f);
                ImGui::DragFloat3("Scale", glm::value_ptr(transform->GetScale()), 0.1f);
            }
        }

        // SpriteRendererComponent
        if (auto &&spriteRenderer = registry.try_get<MCEngine::SpriteRendererComponent>(m_SelectedEntity))
        {
            std::string header =
                "Sprite Renderer Component##" + std::to_string(static_cast<uint32_t>(m_SelectedEntity));
            if (ImGui::CollapsingHeader(header.c_str(), ImGuiTreeNodeFlags_DefaultOpen))
            {
                ImGui::ColorEdit4("Color", glm::value_ptr(spriteRenderer->GetColor()));
            }
        }

        // MeshRendererComponent
        if (auto &&meshRenderer = registry.try_get<MCEngine::MeshRendererComponent>(m_SelectedEntity))
        {
            std::string header = "Mesh Renderer Component##" + std::to_string(static_cast<uint32_t>(m_SelectedEntity));
            if (ImGui::CollapsingHeader(header.c_str(), ImGuiTreeNodeFlags_DefaultOpen))
            {
                ImGui::ColorEdit4("Color", glm::value_ptr(meshRenderer->GetMaterial().GetColor()));
                ImGui::DragFloat("Ambient", &meshRenderer->GetMaterial().GetAmbientStrength(), 0.1f, 0.0f, 1.0f);
                ImGui::DragFloat("Diffuse", &meshRenderer->GetMaterial().GetDiffuseStrength(), 0.1f, 0.0f, 1.0f);
                ImGui::DragFloat("Specular", &meshRenderer->GetMaterial().GetSpecularStrength(), 0.1f, 0.0f, 1.0f);
                ImGui::DragFloat("Shininess", &meshRenderer->GetMaterial().GetShininess(), 1.0f, 1.0f, 256.0f);
            }
        }

        // LightComponent
        if (auto &&light = registry.try_get<MCEngine::LightComponent>(m_SelectedEntity))
        {
            std::string header = "Light Component##" + std::to_string(static_cast<uint32_t>(m_SelectedEntity));
            if (ImGui::CollapsingHeader(header.c_str(), ImGuiTreeNodeFlags_DefaultOpen))
            {
                ImGui::ColorEdit3("Light Color", glm::value_ptr(light->GetColor()));
                ImGui::DragFloat("Intensity", &light->GetIntensity(), 1.0f, 0.0f, 100.0f);
            }
        }
    }
}
