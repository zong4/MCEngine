#include "CameraController.hpp"

#include <imgui.h>

void MCEditor::CameraController::OnStart()
{
    ENGINE_PROFILE_FUNCTION();

    auto &&transform = GetComponent<MCEngine::TransformComponent>();
    transform.SetPosition(glm::vec3(0.0f, 0.0f, 15.0f));
    transform.SetRotation(glm::vec3(0.0f, 0.0f, 0.0f));
    transform.SetScale(glm::vec3(1.0f));
}

void MCEditor::CameraController::OnUpdate(float deltaTime)
{
    ENGINE_PROFILE_FUNCTION();

    auto &&transform = GetComponent<MCEngine::TransformComponent>();
    std::pair<double, double> mouseDelta = MCEngine::MouseLibrary::GetInstance().GetDeltaPosition();
    if (MCEngine::MouseLibrary::GetInstance().IsButtonDown(ENGINE_MOUSE_BUTTON_LEFT))
    {
        transform.SetPosition(transform.GetPosition() + (-transform.GetRight() * (float)mouseDelta.first +
                                                         transform.GetUp() * (float)mouseDelta.second) *
                                                            m_MoveSpeed * deltaTime);
    }
    else if (MCEngine::MouseLibrary::GetInstance().IsButtonDown(ENGINE_MOUSE_BUTTON_RIGHT))
    {
        transform.SetRotation(transform.GetRotation() +
                              glm::vec3((float)mouseDelta.second, (float)mouseDelta.first, 0.0f) * m_RotateSpeed *
                                  deltaTime);
    }

    const std::pair<double, double> &scrollOffset = MCEngine::MouseLibrary::GetInstance().GetScrollOffset();
    if (scrollOffset.second != 0.0)
    {
        transform.SetPosition(transform.GetPosition() +
                              transform.GetForward() * (float)scrollOffset.second * m_ZoomSpeed * deltaTime);
        MCEngine::MouseLibrary::GetInstance().SetScrollOffset(0.0, 0.0);
    }
}
