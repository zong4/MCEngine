#include "CameraController.hpp"

#include <imgui.h>

void MCEditor::CameraController::OnStart() { ENGINE_PROFILE_FUNCTION(); }

void MCEditor::CameraController::OnUpdate(float deltaTime)
{
    ENGINE_PROFILE_FUNCTION();

    auto &&transform = GetComponent<MCEngine::TransformComponent>();

    if (MCEngine::KeyCodeLibrary::GetInstance().IsKeyDown(ENGINE_KEY_I))
        transform.SetPosition(transform.GetPosition() + glm::vec3(0.0f, 1.0f, 0.0f) * m_MoveSpeed * deltaTime);
    if (MCEngine::KeyCodeLibrary::GetInstance().IsKeyDown(ENGINE_KEY_K))
        transform.SetPosition(transform.GetPosition() - glm::vec3(0.0f, 1.0f, 0.0f) * m_MoveSpeed * deltaTime);
    if (MCEngine::KeyCodeLibrary::GetInstance().IsKeyDown(ENGINE_KEY_J))
        transform.SetPosition(transform.GetPosition() - glm::vec3(1.0f, 0.0f, 0.0f) * m_MoveSpeed * deltaTime);
    if (MCEngine::KeyCodeLibrary::GetInstance().IsKeyDown(ENGINE_KEY_L))
        transform.SetPosition(transform.GetPosition() + glm::vec3(1.0f, 0.0f, 0.0f) * m_MoveSpeed * deltaTime);
    if (MCEngine::KeyCodeLibrary::GetInstance().IsKeyDown(ENGINE_KEY_U))
        transform.SetPosition(transform.GetPosition() - glm::vec3(0.0f, 0.0f, 1.0f) * m_MoveSpeed * deltaTime);
    if (MCEngine::KeyCodeLibrary::GetInstance().IsKeyDown(ENGINE_KEY_O))
        transform.SetPosition(transform.GetPosition() + glm::vec3(0.0f, 0.0f, 1.0f) * m_MoveSpeed * deltaTime);
}
