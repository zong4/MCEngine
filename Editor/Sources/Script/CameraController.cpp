#include "CameraController.hpp"

#include <imgui.h>

void MCEditor::CameraController::OnStart()
{
    ENGINE_PROFILE_FUNCTION();

    auto &&transform = GetComponent<MCEngine::TransformComponent>();
    transform.SetPosition(glm::vec3(0.0f, 5.0f, 8.0f));
    transform.SetRotation(glm::vec3(-30.0f, 0.0f, 0.0f));
}

void MCEditor::CameraController::OnUpdate(float deltaTime)
{
    ENGINE_PROFILE_FUNCTION();

    auto &&transform = GetComponent<MCEngine::TransformComponent>();

    if (ImGui::IsKeyDown(ImGuiKey_W))
        transform.SetPosition(transform.GetPosition() + glm::vec3(0.0f, 1.0f, 0.0f) * m_CameraMoveSpeed * deltaTime);
    if (ImGui::IsKeyDown(ImGuiKey_S))
        transform.SetPosition(transform.GetPosition() - glm::vec3(0.0f, 1.0f, 0.0f) * m_CameraMoveSpeed * deltaTime);
    if (ImGui::IsKeyDown(ImGuiKey_A))
        transform.SetPosition(transform.GetPosition() - glm::vec3(1.0f, 0.0f, 0.0f) * m_CameraMoveSpeed * deltaTime);
    if (ImGui::IsKeyDown(ImGuiKey_D))
        transform.SetPosition(transform.GetPosition() + glm::vec3(1.0f, 0.0f, 0.0f) * m_CameraMoveSpeed * deltaTime);
    if (ImGui::IsKeyDown(ImGuiKey_Q))
        transform.SetPosition(transform.GetPosition() - glm::vec3(0.0f, 0.0f, 1.0f) * m_CameraMoveSpeed * deltaTime);
    if (ImGui::IsKeyDown(ImGuiKey_E))
        transform.SetPosition(transform.GetPosition() + glm::vec3(0.0f, 0.0f, 1.0f) * m_CameraMoveSpeed * deltaTime);
}
