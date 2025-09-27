#include "EditorLayer.hpp"

MCEngine::EditorLayer::EditorLayer() : Layer("EditorLayer")
{
    ENGINE_PROFILE_FUNCTION();

    // Initialize cameras
    m_OrthoCamera = std::make_shared<OrthoCamera>(glm::vec3(8.0f, 6.0f, 10.0f));
    m_PerspectiveCamera =
        std::make_shared<PerspectiveCamera>(45.0f, 4.0f / 3.0f, 0.1f, 100.0f, glm::vec3(0.0f, 0.0f, 10.0f));
    m_Camera = m_OrthoCamera;

    // Initialize scene
    m_Scene.AddSquare(
        TransformComponent(glm::vec3(0.0f), glm::vec3(0.0f), glm::vec3(3.0f)),
        SpriteRendererComponent(VAOLibrary::GetInstance().GetVAO("IdentitySquare"), glm::vec4(1.0f, 0.0f, 0.0f, 1.0f)));
    m_Scene.AddCube(TransformComponent(), MeshRendererComponent(VAOLibrary::GetInstance().GetVAO("IdentityCube"),
                                                                glm::vec4(0.0f, 0.0f, 1.0f, 1.0f)));
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

    // Switch camera
    {
        if (KeyCodeLibrary::GetInstance().IsKeyDown(ENGINE_KEY_1))
        {
            m_Camera = m_OrthoCamera;
        }
        if (KeyCodeLibrary::GetInstance().IsKeyDown(ENGINE_KEY_2))
        {
            m_Camera = m_PerspectiveCamera;
        }
    }

    // Move camera
    {
        if (KeyCodeLibrary::GetInstance().IsKeyDown(ENGINE_KEY_W))
        {
            m_Camera->SetPosition(m_Camera->GetPosition() + glm::vec3(0.0f, m_CameraMoveSpeed * deltaTime, 0.0f));
        }
        if (KeyCodeLibrary::GetInstance().IsKeyDown(ENGINE_KEY_S))
        {
            m_Camera->SetPosition(m_Camera->GetPosition() + glm::vec3(0.0f, -m_CameraMoveSpeed * deltaTime, 0.0f));
        }
        if (KeyCodeLibrary::GetInstance().IsKeyDown(ENGINE_KEY_A))
        {
            m_Camera->SetPosition(m_Camera->GetPosition() + glm::vec3(-m_CameraMoveSpeed * deltaTime, 0.0f, 0.0f));
        }
        if (KeyCodeLibrary::GetInstance().IsKeyDown(ENGINE_KEY_D))
        {
            m_Camera->SetPosition(m_Camera->GetPosition() + glm::vec3(m_CameraMoveSpeed * deltaTime, 0.0f, 0.0f));
        }
        if (KeyCodeLibrary::GetInstance().IsKeyDown(ENGINE_KEY_Q))
        {
            m_Camera->SetPosition(m_Camera->GetPosition() + glm::vec3(0.0f, 0.0f, m_CameraMoveSpeed * deltaTime));
        }
        if (KeyCodeLibrary::GetInstance().IsKeyDown(ENGINE_KEY_E))
        {
            m_Camera->SetPosition(m_Camera->GetPosition() + glm::vec3(0.0f, 0.0f, -m_CameraMoveSpeed * deltaTime));
        }
    }

    // Rotate camera
    {
        if (KeyCodeLibrary::GetInstance().IsKeyDown(ENGINE_KEY_I))
        {
            m_Camera->SetRotation(m_Camera->GetRotation() + glm::vec3(-m_CameraRotateSpeed * deltaTime, 0.0f, 0.0f));
        }
        if (KeyCodeLibrary::GetInstance().IsKeyDown(ENGINE_KEY_K))
        {
            m_Camera->SetRotation(m_Camera->GetRotation() + glm::vec3(m_CameraRotateSpeed * deltaTime, 0.0f, 0.0f));
        }
        if (KeyCodeLibrary::GetInstance().IsKeyDown(ENGINE_KEY_J))
        {
            m_Camera->SetRotation(m_Camera->GetRotation() + glm::vec3(0.0f, -m_CameraRotateSpeed * deltaTime, 0.0f));
        }
        if (KeyCodeLibrary::GetInstance().IsKeyDown(ENGINE_KEY_L))
        {
            m_Camera->SetRotation(m_Camera->GetRotation() + glm::vec3(0.0f, m_CameraRotateSpeed * deltaTime, 0.0f));
        }
        if (KeyCodeLibrary::GetInstance().IsKeyDown(ENGINE_KEY_U))
        {
            m_Camera->SetRotation(m_Camera->GetRotation() + glm::vec3(0.0f, 0.0f, m_CameraRotateSpeed * deltaTime));
        }
        if (KeyCodeLibrary::GetInstance().IsKeyDown(ENGINE_KEY_O))
        {
            m_Camera->SetRotation(m_Camera->GetRotation() + glm::vec3(0.0f, 0.0f, -m_CameraRotateSpeed * deltaTime));
        }
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