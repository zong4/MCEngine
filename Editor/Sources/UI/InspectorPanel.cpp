#include "InspectorPanel.hpp"

#include <imgui.h>
#include <imgui_internal.h>

// clang-format off
template <typename T, typename UIFunction>
// clang-format on
static void DrawTable2(const std::string &label, UIFunction &&uiFunction)
{
    ENGINE_PROFILE_FUNCTION();

    ImGui::BeginTable(label.c_str(), 2, ImGuiTableFlags_SizingStretchProp | ImGuiTableFlags_NoPadOuterX);
    ImGui::TableSetupColumn("Label", ImGuiTableColumnFlags_None, 0.16f);
    ImGui::TableSetupColumn("Value", ImGuiTableColumnFlags_None, 0.84f);
    ImGui::TableNextRow();

    // Label
    ImGui::TableSetColumnIndex(0);
    ImGui::TextUnformatted(label.c_str());

    // Value
    ImGui::TableSetColumnIndex(1);
    ImGui::SetNextItemWidth(-FLT_MIN);
    uiFunction();

    ImGui::EndTable();
}

// clang-format off
template <typename T, typename UIFunction>
// clang-format on
static void DrawComponent(const std::string &name, MCEngine::Entity entity, UIFunction &&uiFunction,
                          bool removeable = true)
{
    ENGINE_PROFILE_FUNCTION();

    if (entity.HasComponent<T>())
    {
        std::string header = name + "##" + std::to_string(static_cast<uint32_t>(entity));

        if (removeable)
        {
            bool open = true;
            if (ImGui::CollapsingHeader(header.c_str(), &open, ImGuiTreeNodeFlags_DefaultOpen))
            {
                ImGui::PushID(header.c_str());
                uiFunction(entity.GetComponent<T>());
                ImGui::PopID();
            }

            if (!open)
            {
                entity.RemoveComponent<T>();
            }
        }
        else
        {
            if (ImGui::CollapsingHeader(header.c_str(), ImGuiTreeNodeFlags_DefaultOpen))
            {
                ImGui::PushID(header.c_str());
                uiFunction(entity.GetComponent<T>());
                ImGui::PopID();
            }
        }
    }
}

void MCEditor::InspectorPanel::OnImGuiRender(MCEngine::Entity m_SelectedEntity) const
{
    ENGINE_PROFILE_FUNCTION();

    if (m_SelectedEntity)
    {
        // TagComponent
        DrawComponent<MCEngine::TagComponent>(
            "Tag Component", m_SelectedEntity,
            [](MCEngine::TagComponent &tag) {
                DrawTable2<MCEngine::TagComponent>("Tag", [&tag]() {
                    char buffer[256];
                    memset(buffer, 0, sizeof(buffer));
                    strncpy(buffer, tag.GetTag().c_str(), sizeof(buffer) - 1);
                    if (ImGui::InputText("##Tag", buffer, sizeof(buffer)))
                    {
                        tag.SetTag(std::string(buffer));
                    }
                });
            },
            false);

        // TransformComponent
        DrawComponent<MCEngine::TransformComponent>("Transform Component", m_SelectedEntity,
                                                    [](MCEngine::TransformComponent &transform) {
                                                        DrawVec3Control("Position", transform.GetPosition(), 0.0f);
                                                        DrawVec3Control("Rotation", transform.GetRotation(), 0.0f);
                                                        DrawVec3Control("Scale", transform.GetScale(), 1.0f);
                                                    });

        // CameraComponent
        DrawComponent<MCEngine::CameraComponent>(
            "Camera Component", m_SelectedEntity, [](MCEngine::CameraComponent &camera) {
                DrawTable2<MCEngine::CameraComponent>("Type", [&camera]() {
                    const char *cameraTypes[] = {"Orthographic", "Perspective"};
                    int currentType = static_cast<int>(camera.GetType());
                    if (ImGui::Combo("##Camera Type", &currentType, cameraTypes, IM_ARRAYSIZE(cameraTypes)))
                    {
                        camera.SetType(static_cast<MCEngine::CameraType>(currentType));
                    }
                });

                if (camera.GetType() == MCEngine::CameraType::Orthographic)
                {
                    DrawTable2<MCEngine::CameraComponent>("Scale", [&camera]() {
                        auto &&scale = camera.GetScale();
                        if (ImGui::DragFloat("##Scale", &scale, 1.0f, 0.1f, 10.0f))
                        {
                            camera.SetScale(scale);
                        }
                    });
                }

                if (camera.GetType() == MCEngine::CameraType::Perspective)
                {
                    DrawTable2<MCEngine::CameraComponent>("FOV", [&camera]() {
                        auto &&fov = camera.GetFOV();
                        if (ImGui::DragFloat("##FOV", &fov, 1.0f, 1.0f, 120.0f))
                        {
                            camera.SetFOV(fov);
                        }
                    });
                    DrawTable2<MCEngine::CameraComponent>("Near Clip", [&camera]() {
                        auto &&nearClip = camera.GetNearClip();
                        if (ImGui::DragFloat("##Near Clip", &nearClip, 0.1f, 0.01f, 100.0f))
                        {
                            camera.SetNearClip(nearClip);
                        }
                    });
                    DrawTable2<MCEngine::CameraComponent>("Far Clip", [&camera]() {
                        auto &&farClip = camera.GetFarClip();
                        if (ImGui::DragFloat("##Far Clip", &farClip, 1.0f, 10.0f, 1000.0f))
                        {
                            camera.SetFarClip(farClip);
                        }
                    });
                }
            });

        // SpriteRendererComponent
        DrawComponent<MCEngine::SpriteRendererComponent>(
            "Sprite Renderer Component", m_SelectedEntity, [](MCEngine::SpriteRendererComponent &sprite) {
                DrawTable2<MCEngine::SpriteRendererComponent>(
                    "Color", [&sprite]() { ImGui::ColorEdit4("##Color", glm::value_ptr(sprite.GetColor())); });
            });

        // MeshRendererComponent
        DrawComponent<MCEngine::MeshRendererComponent>(
            "Mesh Renderer Component", m_SelectedEntity, [](MCEngine::MeshRendererComponent &meshRenderer) {
                DrawTable2<MCEngine::MeshRendererComponent>("Color", [&meshRenderer]() {
                    ImGui::ColorEdit4("##Color", glm::value_ptr(meshRenderer.GetMaterial().GetColor()));
                });
                DrawTable2<MCEngine::MeshRendererComponent>("Ambient", [&meshRenderer]() {
                    ImGui::DragFloat("##Ambient", &meshRenderer.GetMaterial().GetAmbientStrength(), 0.1f, 0.0f, 1.0f);
                });
                DrawTable2<MCEngine::MeshRendererComponent>("Diffuse", [&meshRenderer]() {
                    ImGui::DragFloat("##Diffuse", &meshRenderer.GetMaterial().GetDiffuseStrength(), 0.1f, 0.0f, 1.0f);
                });
                DrawTable2<MCEngine::MeshRendererComponent>("Specular", [&meshRenderer]() {
                    ImGui::DragFloat("##Specular", &meshRenderer.GetMaterial().GetSpecularStrength(), 0.1f, 0.0f, 1.0f);
                });
                DrawTable2<MCEngine::MeshRendererComponent>("Shininess", [&meshRenderer]() {
                    ImGui::DragFloat("##Shininess", &meshRenderer.GetMaterial().GetShininess(), 1.0f, 1.0f, 256.0f);
                });
            });

        // LightComponent
        DrawComponent<MCEngine::LightComponent>(
            "Light Component", m_SelectedEntity, [](MCEngine::LightComponent &light) {
                DrawTable2<MCEngine::LightComponent>(
                    "Color", [&light]() { ImGui::ColorEdit3("##Color", glm::value_ptr(light.GetColor())); });
                DrawTable2<MCEngine::LightComponent>("Intensity", [&light]() {
                    ImGui::DragFloat("##Intensity", &light.GetIntensity(), 0.1f, 0.0f, 10.0f);
                });

                if (light.GetType() == MCEngine::LightType::Point || light.GetType() == MCEngine::LightType::Spot)
                {
                    DrawTable2<MCEngine::LightComponent>("Constant", [&light]() {
                        ImGui::DragFloat("##Constant", &light.GetConstant(), 0.01f, 0.0f, 1.0f);
                    });
                    DrawTable2<MCEngine::LightComponent>(
                        "Linear", [&light]() { ImGui::DragFloat("##Linear", &light.GetLinear(), 0.001f, 0.0f, 1.0f); });
                    DrawTable2<MCEngine::LightComponent>("Quadratic", [&light]() {
                        ImGui::DragFloat("##Quadratic", &light.GetQuadratic(), 0.0001f, 0.0f, 1.0f);
                    });

                    if (light.GetType() == MCEngine::LightType::Spot)
                    {
                        DrawTable2<MCEngine::LightComponent>("CutOff", [&light]() {
                            ImGui::DragFloat("##CutOff", &light.GetInnerAngle(), 1.0f, 0.0f, 90.0f);
                        });
                        DrawTable2<MCEngine::LightComponent>("Outer CutOff", [&light]() {
                            ImGui::DragFloat("##Outer CutOff", &light.GetOuterAngle(), 1.0f, 0.0f, 90.0f);
                        });
                    }
                }
            });

        DrawAddComponentButton(m_SelectedEntity);
    }
}

void MCEditor::InspectorPanel::DrawVec3Control(const std::string &label, glm::vec3 &values, float resetValue)
{
    ENGINE_PROFILE_FUNCTION();

    ImGui::PushID(label.c_str());

    ImGui::BeginTable("Vec3Table", 4, ImGuiTableFlags_SizingStretchProp | ImGuiTableFlags_NoPadOuterX);
    ImGui::TableSetupColumn(label.c_str(), ImGuiTableColumnFlags_None, 0.16f);
    ImGui::TableSetupColumn("X", ImGuiTableColumnFlags_None, 0.28f);
    ImGui::TableSetupColumn("Y", ImGuiTableColumnFlags_None, 0.28f);
    ImGui::TableSetupColumn("Z", ImGuiTableColumnFlags_None, 0.28f);
    ImGui::TableNextRow();

    // Label
    ImGui::TableSetColumnIndex(0);
    ImGui::TextUnformatted(label.c_str());

    float lineHeight = ImGui::GetFontSize() + ImGui::GetStyle().FramePadding.y * 2.0f;
    ImVec2 buttonSize = {lineHeight + 3.0f, lineHeight};

    // X
    ImGui::TableSetColumnIndex(1);
    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{0.8f, 0.1f, 0.15f, 1.0f});
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{0.9f, 0.2f, 0.2f, 1.0f});
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{0.8f, 0.1f, 0.15f, 1.0f});
    if (ImGui::Button("X", buttonSize))
        values.x = resetValue;
    ImGui::PopStyleColor(3);
    ImGui::SameLine();
    ImGui::SetNextItemWidth(-FLT_MIN);
    ImGui::DragFloat("##X", &values.x, 0.1f);

    // Y
    ImGui::TableSetColumnIndex(2);
    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{0.2f, 0.7f, 0.2f, 1.0f});
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{0.3f, 0.8f, 0.3f, 1.0f});
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{0.2f, 0.7f, 0.2f, 1.0f});
    if (ImGui::Button("Y", buttonSize))
        values.y = resetValue;
    ImGui::PopStyleColor(3);
    ImGui::SameLine();
    ImGui::SetNextItemWidth(-FLT_MIN);
    ImGui::DragFloat("##Y", &values.y, 0.1f);

    // Z
    ImGui::TableSetColumnIndex(3);
    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{0.1f, 0.25f, 0.8f, 1.0f});
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{0.2f, 0.35f, 0.9f, 1.0f});
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{0.1f, 0.25f, 0.8f, 1.0f});
    if (ImGui::Button("Z", buttonSize))
        values.z = resetValue;
    ImGui::PopStyleColor(3);
    ImGui::SameLine();
    ImGui::SetNextItemWidth(-FLT_MIN);
    ImGui::DragFloat("##Z", &values.z, 0.1f);

    ImGui::EndTable();

    ImGui::PopID();
}

void MCEditor::InspectorPanel::DrawAddComponentButton(MCEngine::Entity entity)
{
    ENGINE_PROFILE_FUNCTION();

    ImGui::Separator();

    if (ImGui::Button("Add Component", ImVec2(ImGui::GetContentRegionAvail().x, 0)))
        ImGui::OpenPopup("AddComponent");

    if (ImGui::BeginPopup("AddComponent"))
    {
        if (!entity.HasComponent<MCEngine::SpriteRendererComponent>())
        {
            if (ImGui::MenuItem("Sprite Renderer Component"))
            {
                entity.AddComponent<MCEngine::SpriteRendererComponent>(
                    MCEngine::VAOLibrary::GetInstance().GetVAO("Square"));
                ImGui::CloseCurrentPopup();
            }
        }

        if (!entity.HasComponent<MCEngine::MeshRendererComponent>())
        {
            if (ImGui::MenuItem("Mesh Renderer Component"))
            {
                entity.AddComponent<MCEngine::MeshRendererComponent>(
                    MCEngine::VAOLibrary::GetInstance().GetVAO("Cube"));
                ImGui::CloseCurrentPopup();
            }
        }

        if (!entity.HasComponent<MCEngine::CameraComponent>())
        {
            if (ImGui::MenuItem("Orthographic Camera Component"))
            {
                entity.AddComponent<MCEngine::CameraComponent>(MCEngine::CameraType::Orthographic);
                ImGui::CloseCurrentPopup();
            }
        }

        if (!entity.HasComponent<MCEngine::CameraComponent>())
        {
            if (ImGui::MenuItem("Perspective Camera Component"))
            {
                entity.AddComponent<MCEngine::CameraComponent>(MCEngine::CameraType::Perspective);
                ImGui::CloseCurrentPopup();
            }
        }

        if (!entity.HasComponent<MCEngine::LightComponent>())
        {
            if (ImGui::MenuItem("Directional Light Component"))
            {
                entity.AddComponent<MCEngine::LightComponent>(MCEngine::LightType::Directional);
                ImGui::CloseCurrentPopup();
            }
        }

        if (!entity.HasComponent<MCEngine::LightComponent>())
        {
            if (ImGui::MenuItem("Point Light Component"))
            {
                entity.AddComponent<MCEngine::LightComponent>(MCEngine::LightType::Point);
                ImGui::CloseCurrentPopup();
            }
        }

        if (!entity.HasComponent<MCEngine::LightComponent>())
        {
            if (ImGui::MenuItem("Spot Light Component"))
            {
                entity.AddComponent<MCEngine::LightComponent>(MCEngine::LightType::Spot);
                ImGui::CloseCurrentPopup();
            }
        }

        ImGui::EndPopup();
    }
}