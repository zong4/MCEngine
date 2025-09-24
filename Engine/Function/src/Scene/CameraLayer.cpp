#include "CameraLayer.hpp"

MCEngine::CameraLayer::CameraLayer() : Layer("CameraLayer")
{
    m_Camera = std::make_shared<OrthoCamera>(glm::vec2(0.5f, 0.0f), glm::vec2(8.0f, 6.0f));
}

void MCEngine::CameraLayer::OnEvent(Event &event)
{
    EventDispatcher dispatcher(event);
    dispatcher.Dispatch<KeyEvent>([this](KeyEvent &e) {
        if (e.GetAction() == 1) // Press
        {
            switch (e.GetKeyCode())
            {
            case ENGINE_KEY_W:
                m_Camera->SetPosition(m_Camera->GetPosition() + glm::vec3(0.0f, m_CameraMoveSpeed, 0.0f));
                break;
            case ENGINE_KEY_S:
                m_Camera->SetPosition(m_Camera->GetPosition() - glm::vec3(0.0f, m_CameraMoveSpeed, 0.0f));
                break;
            case ENGINE_KEY_A:
                m_Camera->SetPosition(m_Camera->GetPosition() - glm::vec3(m_CameraMoveSpeed, 0.0f, 0.0f));
                break;
            case ENGINE_KEY_D:
                m_Camera->SetPosition(m_Camera->GetPosition() + glm::vec3(m_CameraMoveSpeed, 0.0f, 0.0f));
                break;
            default:
                break;
            }
        }
        return false;
    });
}

void MCEngine::CameraLayer::OnUpdate() {}