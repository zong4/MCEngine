#include "EditorLayer.hpp"

MCEngine::EditorLayer::EditorLayer(std::shared_ptr<Camera> sceneCameraPtr, std::shared_ptr<Camera> gameCameraPtr)
    : Layer("EditorLayer"), m_SceneCameraPtr(sceneCameraPtr), m_GameCameraPtr(gameCameraPtr)
{
    ENGINE_PROFILE_FUNCTION();

    // Default to scene camera
    m_CameraPtr = m_SceneCameraPtr;

    // Initialize 2D scene
    m_Scene2D.AddSquare(TransformComponent(glm::vec3(0.0f), glm::vec3(0.0f), glm::vec3(3.0f)),
                        SpriteRendererComponent(VAOLibrary::GetInstance().GetVAO("IdentitySquare"),
                                                glm::vec4(1.0f, 0.7f, 0.8f, 1.0f),
                                                TextureLibrary::GetInstance().GetTexture("02BG")));

    // Initialize 3D scene
    m_Scene3D.AddCube(TransformComponent(), MeshRendererComponent(VAOLibrary::GetInstance().GetVAO("IdentityCube"),
                                                                  glm::vec4(0.0f, 0.0f, 1.0f, 0.8f)));
}

void MCEngine::EditorLayer::OnEvent(Event &event)
{
    ENGINE_PROFILE_FUNCTION();

    EventDispatcher dispatcher(event);
    dispatcher.Dispatch<KeyEvent>([this](KeyEvent &e) {
        KeyCodeLibrary::GetInstance().SetKeyAction(e.GetKeyCode(), e.GetAction());
        return true;
    });

    m_CameraPtr->OnEvent(event);

    m_Scene2D.OnEvent(event);
    m_Scene3D.OnEvent(event);
}

void MCEngine::EditorLayer::OnUpdate(float deltaTime)
{
    ENGINE_PROFILE_FUNCTION();

    // Switch camera
    {
        if (KeyCodeLibrary::GetInstance().IsKeyDown(ENGINE_KEY_1))
        {
            m_CameraPtr = m_SceneCameraPtr;
        }
        if (KeyCodeLibrary::GetInstance().IsKeyDown(ENGINE_KEY_2))
        {
            m_CameraPtr = m_GameCameraPtr;
        }
    }

    // Move camera
    {
        if (KeyCodeLibrary::GetInstance().IsKeyDown(ENGINE_KEY_W))
        {
            m_CameraPtr->SetPosition(m_CameraPtr->GetPosition() + glm::vec3(0.0f, m_CameraMoveSpeed * deltaTime, 0.0f));
        }
        if (KeyCodeLibrary::GetInstance().IsKeyDown(ENGINE_KEY_S))
        {
            m_CameraPtr->SetPosition(m_CameraPtr->GetPosition() +
                                     glm::vec3(0.0f, -m_CameraMoveSpeed * deltaTime, 0.0f));
        }
        if (KeyCodeLibrary::GetInstance().IsKeyDown(ENGINE_KEY_A))
        {
            m_CameraPtr->SetPosition(m_CameraPtr->GetPosition() +
                                     glm::vec3(-m_CameraMoveSpeed * deltaTime, 0.0f, 0.0f));
        }
        if (KeyCodeLibrary::GetInstance().IsKeyDown(ENGINE_KEY_D))
        {
            m_CameraPtr->SetPosition(m_CameraPtr->GetPosition() + glm::vec3(m_CameraMoveSpeed * deltaTime, 0.0f, 0.0f));
        }
        if (KeyCodeLibrary::GetInstance().IsKeyDown(ENGINE_KEY_Q))
        {
            m_CameraPtr->SetPosition(m_CameraPtr->GetPosition() + glm::vec3(0.0f, 0.0f, m_CameraMoveSpeed * deltaTime));
        }
        if (KeyCodeLibrary::GetInstance().IsKeyDown(ENGINE_KEY_E))
        {
            m_CameraPtr->SetPosition(m_CameraPtr->GetPosition() +
                                     glm::vec3(0.0f, 0.0f, -m_CameraMoveSpeed * deltaTime));
        }
    }

    // Rotate camera
    {
        if (KeyCodeLibrary::GetInstance().IsKeyDown(ENGINE_KEY_I))
        {
            m_CameraPtr->SetRotation(m_CameraPtr->GetRotation() +
                                     glm::vec3(-m_CameraRotateSpeed * deltaTime, 0.0f, 0.0f));
        }
        if (KeyCodeLibrary::GetInstance().IsKeyDown(ENGINE_KEY_K))
        {
            m_CameraPtr->SetRotation(m_CameraPtr->GetRotation() +
                                     glm::vec3(m_CameraRotateSpeed * deltaTime, 0.0f, 0.0f));
        }
        if (KeyCodeLibrary::GetInstance().IsKeyDown(ENGINE_KEY_J))
        {
            m_CameraPtr->SetRotation(m_CameraPtr->GetRotation() +
                                     glm::vec3(0.0f, -m_CameraRotateSpeed * deltaTime, 0.0f));
        }
        if (KeyCodeLibrary::GetInstance().IsKeyDown(ENGINE_KEY_L))
        {
            m_CameraPtr->SetRotation(m_CameraPtr->GetRotation() +
                                     glm::vec3(0.0f, m_CameraRotateSpeed * deltaTime, 0.0f));
        }
        if (KeyCodeLibrary::GetInstance().IsKeyDown(ENGINE_KEY_U))
        {
            m_CameraPtr->SetRotation(m_CameraPtr->GetRotation() +
                                     glm::vec3(0.0f, 0.0f, m_CameraRotateSpeed * deltaTime));
        }
        if (KeyCodeLibrary::GetInstance().IsKeyDown(ENGINE_KEY_O))
        {
            m_CameraPtr->SetRotation(m_CameraPtr->GetRotation() +
                                     glm::vec3(0.0f, 0.0f, -m_CameraRotateSpeed * deltaTime));
        }
    }

    // Update camera
    m_CameraPtr->Update(deltaTime);

    // Update objects
    m_Scene2D.Update(deltaTime);
    m_Scene3D.Update(deltaTime);
}

void MCEngine::EditorLayer::OnRender()
{
    ENGINE_PROFILE_FUNCTION();

    m_Scene2D.Render(m_CameraPtr);
    m_Scene3D.Render(m_CameraPtr);
}