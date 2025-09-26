#include "EditorLayer.hpp"

MCEngine::EditorLayer::EditorLayer() : Layer("EditorLayer")
{
    ENGINE_PROFILE_FUNCTION();

    // Initialize cameras
    m_OrthoCamera = std::make_shared<OrthoCamera>(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(8.0f, 6.0f));
    m_PerspectiveCamera =
        std::make_shared<PerspectiveCamera>(glm::vec3(0.0f, 0.0f, 3.0f), 45.0f, 4.0f / 3.0f, 0.1f, 100.0f);
    m_Camera = m_OrthoCamera;
}

void MCEngine::EditorLayer::OnEvent(Event &event)
{
    ENGINE_PROFILE_FUNCTION();

    // todo Move to other place
    EventDispatcher dispatcher(event);
    dispatcher.Dispatch<KeyEvent>([this](KeyEvent &e) {
        KeyCodeLibrary::GetInstance().SetKeyAction(e.GetKeyCode(), e.GetAction());
        return true;
    });

    m_Camera->OnEvent(event);

    m_Scene.OnEvent(event);
}

void MCEngine::EditorLayer::OnUpdate(float deltaTime)
{
    ENGINE_PROFILE_FUNCTION();

    if (KeyCodeLibrary::GetInstance().GetKeyAction(ENGINE_KEY_W) == 1 ||
        KeyCodeLibrary::GetInstance().GetKeyAction(ENGINE_KEY_W) == 2)
    {
        m_Camera->SetPosition(m_Camera->GetPosition() + glm::vec3(0.0f, m_CameraMoveSpeed * deltaTime, 0.0f));
    }
    if (KeyCodeLibrary::GetInstance().GetKeyAction(ENGINE_KEY_S) == 1 ||
        KeyCodeLibrary::GetInstance().GetKeyAction(ENGINE_KEY_S) == 2)
    {
        m_Camera->SetPosition(m_Camera->GetPosition() + glm::vec3(0.0f, -m_CameraMoveSpeed * deltaTime, 0.0f));
    }
    if (KeyCodeLibrary::GetInstance().GetKeyAction(ENGINE_KEY_A) == 1 ||
        KeyCodeLibrary::GetInstance().GetKeyAction(ENGINE_KEY_A) == 2)
    {
        m_Camera->SetPosition(m_Camera->GetPosition() + glm::vec3(-m_CameraMoveSpeed * deltaTime, 0.0f, 0.0f));
    }
    if (KeyCodeLibrary::GetInstance().GetKeyAction(ENGINE_KEY_D) == 1 ||
        KeyCodeLibrary::GetInstance().GetKeyAction(ENGINE_KEY_D) == 2)
    {
        m_Camera->SetPosition(m_Camera->GetPosition() + glm::vec3(m_CameraMoveSpeed * deltaTime, 0.0f, 0.0f));
    }

    // Update camera
    m_Camera->Update(deltaTime);

    // Update objects
    m_Scene.Update(deltaTime);
}

void MCEngine::EditorLayer::OnRender()
{
    ENGINE_PROFILE_FUNCTION();

    m_Scene.Render(m_Camera);
}