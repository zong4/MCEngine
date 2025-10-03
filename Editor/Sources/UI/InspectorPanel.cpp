#include "InspectorPanel.hpp"

#include <imgui.h>
#include <imgui_internal.h>

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
                ImGui::PushID(header.c_str());

                char buffer[256];
                memset(buffer, 0, sizeof(buffer));
                strncpy(buffer, tag->GetTag().c_str(), sizeof(buffer));
                if (ImGui::InputText("Tag", buffer, sizeof(buffer)))
                    tag->SetTag(std::string(buffer));

                ImGui::PopID();
            }
        }

        // TransformComponent
        if (auto &&transform = registry.try_get<MCEngine::TransformComponent>(m_SelectedEntity))
        {
            std::string header = "Transform Component##" + std::to_string(static_cast<uint32_t>(m_SelectedEntity));
            if (ImGui::CollapsingHeader(header.c_str(), ImGuiTreeNodeFlags_DefaultOpen))
            {
                DrawVec3Control("Position", transform->GetPosition());
                DrawVec3Control("Rotation", transform->GetRotation());
                DrawVec3Control("Scale", transform->GetScale(), 1.0f);
            }
        }

        // SpriteRendererComponent
        if (auto &&spriteRenderer = registry.try_get<MCEngine::SpriteRendererComponent>(m_SelectedEntity))
        {
            std::string header =
                "Sprite Renderer Component##" + std::to_string(static_cast<uint32_t>(m_SelectedEntity));

            bool open = true;
            if (ImGui::CollapsingHeader(header.c_str(), &open, ImGuiTreeNodeFlags_DefaultOpen))
            {
                ImGui::PushID(header.c_str());

                ImGui::ColorEdit4("Color", glm::value_ptr(spriteRenderer->GetColor()));

                ImGui::PopID();
            }

            if (!open)
            {
                registry.remove<MCEngine::SpriteRendererComponent>(m_SelectedEntity);
            }
        }

        // MeshRendererComponent
        if (auto &&meshRenderer = registry.try_get<MCEngine::MeshRendererComponent>(m_SelectedEntity))
        {
            std::string header = "Mesh Renderer Component##" + std::to_string(static_cast<uint32_t>(m_SelectedEntity));

            bool open = true;
            if (ImGui::CollapsingHeader(header.c_str(), &open, ImGuiTreeNodeFlags_DefaultOpen))
            {
                ImGui::PushID(header.c_str());

                ImGui::ColorEdit4("Color", glm::value_ptr(meshRenderer->GetMaterial().GetColor()));
                ImGui::DragFloat("Ambient", &meshRenderer->GetMaterial().GetAmbientStrength(), 0.1f, 0.0f, 1.0f);
                ImGui::DragFloat("Diffuse", &meshRenderer->GetMaterial().GetDiffuseStrength(), 0.1f, 0.0f, 1.0f);
                ImGui::DragFloat("Specular", &meshRenderer->GetMaterial().GetSpecularStrength(), 0.1f, 0.0f, 1.0f);
                ImGui::DragFloat("Shininess", &meshRenderer->GetMaterial().GetShininess(), 1.0f, 1.0f, 256.0f);

                ImGui::PopID();
            }

            if (!open)
            {
                registry.remove<MCEngine::MeshRendererComponent>(m_SelectedEntity);
            }
        }

        // CameraComponent
        if (auto &&camera = registry.try_get<MCEngine::CameraComponent>(m_SelectedEntity))
        {
            std::string header = "Camera Component##" + std::to_string(static_cast<uint32_t>(m_SelectedEntity));

            bool open = true;
            if (ImGui::CollapsingHeader(header.c_str(), &open, ImGuiTreeNodeFlags_DefaultOpen))
            {
                ImGui::PushID(header.c_str());

                const char *cameraTypes[] = {"Orthographic", "Perspective"};
                int currentType = static_cast<int>(camera->GetType());
                if (ImGui::Combo("Camera Type", &currentType, cameraTypes, IM_ARRAYSIZE(cameraTypes)))
                {
                    camera->SetType(static_cast<MCEngine::CameraType>(currentType));
                }

                if (camera->GetType() == MCEngine::CameraType::Orthographic)
                {
                    auto &&scale = camera->GetScale();
                    if (ImGui::DragFloat("Scale", &scale, 1.0f, 0.1f, 10.0f))
                    {
                        camera->SetScale(scale);
                    }
                }

                if (camera->GetType() == MCEngine::CameraType::Perspective)
                {
                    auto &&fov = camera->GetFOV();
                    if (ImGui::DragFloat("FOV", &fov, 1.0f, 1.0f, 120.0f))
                    {
                        camera->SetFOV(fov);
                    }
                    auto &&nearClip = camera->GetNearClip();
                    if (ImGui::DragFloat("Near Clip", &nearClip, 0.1f, 0.01f, 100.0f))
                    {
                        camera->SetNearClip(nearClip);
                    }
                    auto &&farClip = camera->GetFarClip();
                    if (ImGui::DragFloat("Far Clip", &farClip, 1.0f, 10.0f, 1000.0f))
                    {
                        camera->SetFarClip(farClip);
                    }
                }

                ImGui::PopID();
            }

            if (!open)
            {
                registry.remove<MCEngine::CameraComponent>(m_SelectedEntity);
            }
        }

        // LightComponent
        if (auto &&light = registry.try_get<MCEngine::LightComponent>(m_SelectedEntity))
        {
            std::string header = "Light Component##" + std::to_string(static_cast<uint32_t>(m_SelectedEntity));

            bool open = true;
            if (ImGui::CollapsingHeader(header.c_str(), &open, ImGuiTreeNodeFlags_DefaultOpen))
            {
                ImGui::PushID(header.c_str());

                ImGui::ColorEdit3("Color", glm::value_ptr(light->GetColor()));
                ImGui::DragFloat("Intensity", &light->GetIntensity(), 0.1f, 0.0f, 10.0f);

                if (light->GetType() == MCEngine::LightType::Point || light->GetType() == MCEngine::LightType::Spot)
                {
                    ImGui::DragFloat("Constant", &light->GetConstant(), 0.01f, 0.0f, 1.0f);
                    ImGui::DragFloat("Linear", &light->GetLinear(), 0.01f, 0.0f, 1.0f);
                    ImGui::DragFloat("Quadratic", &light->GetQuadratic(), 0.01f, 0.0f, 1.0f);
                }

                if (light->GetType() == MCEngine::LightType::Spot)
                {
                    ImGui::DragFloat("CutOff", &light->GetCutOff(), 1.0f, 0.0f, 90.0f);
                    ImGui::DragFloat("Outer CutOff", &light->GetOuterCutOff(), 1.0f, 0.0f, 90.0f);
                }

                ImGui::PopID();
            }

            if (!open)
            {
                registry.remove<MCEngine::LightComponent>(m_SelectedEntity);
            }
        }

        DrawAddComponentButton(registry, m_SelectedEntity);
    }
}

void MCEditor::InspectorPanel::DrawVec3Control(const std::string &label, glm::vec3 &values, float resetValue,
                                               float columnWidth) const
{
    ENGINE_PROFILE_FUNCTION();

    ImGui::PushID(label.c_str());

    ImGui::Columns(2, nullptr, false);
    ImGui::SetColumnWidth(0, columnWidth);
    ImGui::TextUnformatted(label.c_str());
    ImGui::NextColumn();

    ImGui::PushMultiItemsWidths(3, ImGui::CalcItemWidth());
    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{0, 0});

    float lineHeight = ImGui::GetFontSize() + ImGui::GetStyle().FramePadding.y * 2.0f;
    ImVec2 buttonSize = {lineHeight + 3.0f, lineHeight};

    // X
    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{0.8f, 0.1f, 0.15f, 1.0f});
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{0.9f, 0.2f, 0.2f, 1.0f});
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{0.8f, 0.1f, 0.15f, 1.0f});
    if (ImGui::Button("X", buttonSize))
        values.x = resetValue;
    ImGui::PopStyleColor(3);

    ImGui::SameLine();
    ImGui::DragFloat("##X", &values.x, 0.1f);
    ImGui::PopItemWidth();
    ImGui::SameLine();

    // Y
    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{0.2f, 0.7f, 0.2f, 1.0f});
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{0.3f, 0.8f, 0.3f, 1.0f});
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{0.2f, 0.7f, 0.2f, 1.0f});
    if (ImGui::Button("Y", buttonSize))
        values.y = resetValue;
    ImGui::PopStyleColor(3);

    ImGui::SameLine();
    ImGui::DragFloat("##Y", &values.y, 0.1f);
    ImGui::PopItemWidth();
    ImGui::SameLine();

    // Z
    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{0.1f, 0.25f, 0.8f, 1.0f});
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{0.2f, 0.35f, 0.9f, 1.0f});
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{0.1f, 0.25f, 0.8f, 1.0f});
    if (ImGui::Button("Z", buttonSize))
        values.z = resetValue;
    ImGui::PopStyleColor(3);

    ImGui::SameLine();
    ImGui::DragFloat("##Z", &values.z, 0.1f);
    ImGui::PopItemWidth();
    ImGui::SameLine();

    ImGui::PopStyleVar();
    ImGui::Columns(1);
    ImGui::PopID();
}

void MCEditor::InspectorPanel::DrawAddComponentButton(entt::registry &registry, entt::entity m_SelectedEntity) const
{
    ENGINE_PROFILE_FUNCTION();

    ImGui::Separator();

    if (ImGui::Button("Add Component"))
        ImGui::OpenPopup("AddComponent");

    if (ImGui::BeginPopup("AddComponent"))
    {
        if (!registry.any_of<MCEngine::SpriteRendererComponent>(m_SelectedEntity))
        {
            if (ImGui::MenuItem("Sprite Renderer Component"))
            {
                registry.emplace<MCEngine::SpriteRendererComponent>(
                    m_SelectedEntity, MCEngine::VAOLibrary::GetInstance().GetVAO("Square"));
                ImGui::CloseCurrentPopup();
            }
        }

        if (!registry.any_of<MCEngine::MeshRendererComponent>(m_SelectedEntity))
        {
            if (ImGui::MenuItem("Mesh Renderer Component"))
            {
                registry.emplace<MCEngine::MeshRendererComponent>(m_SelectedEntity,
                                                                  MCEngine::VAOLibrary::GetInstance().GetVAO("Cube"));
                ImGui::CloseCurrentPopup();
            }
        }

        if (!registry.any_of<MCEngine::CameraComponent>(m_SelectedEntity))
        {
            if (ImGui::MenuItem("Orthographic Camera Component"))
            {
                registry.emplace<MCEngine::CameraComponent>(m_SelectedEntity, MCEngine::CameraType::Orthographic);
                ImGui::CloseCurrentPopup();
            }
        }

        if (!registry.any_of<MCEngine::CameraComponent>(m_SelectedEntity))
        {
            if (ImGui::MenuItem("Perspective Camera Component"))
            {
                registry.emplace<MCEngine::CameraComponent>(m_SelectedEntity, MCEngine::CameraType::Perspective);
                ImGui::CloseCurrentPopup();
            }
        }

        if (!registry.any_of<MCEngine::LightComponent>(m_SelectedEntity))
        {
            if (ImGui::MenuItem("Directional Light Component"))
            {
                registry.emplace<MCEngine::LightComponent>(m_SelectedEntity, MCEngine::LightType::Directional);
                ImGui::CloseCurrentPopup();
            }
        }

        if (!registry.any_of<MCEngine::LightComponent>(m_SelectedEntity))
        {
            if (ImGui::MenuItem("Point Light Component"))
            {
                registry.emplace<MCEngine::LightComponent>(m_SelectedEntity, MCEngine::LightType::Point);
                ImGui::CloseCurrentPopup();
            }
        }

        if (!registry.any_of<MCEngine::LightComponent>(m_SelectedEntity))
        {
            if (ImGui::MenuItem("Spot Light Component"))
            {
                registry.emplace<MCEngine::LightComponent>(m_SelectedEntity, MCEngine::LightType::Spot);
                ImGui::CloseCurrentPopup();
            }
        }

        ImGui::EndPopup();
    }
}