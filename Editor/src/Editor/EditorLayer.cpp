#include "EditorLayer.hpp"

MCEngine::EditorLayer::EditorLayer() : Layer("EditorLayer")
{
    ENGINE_PROFILE_FUNCTION();

    // Initialize 2D scene
    {
        m_Scene2D = std::make_shared<Scene2D>();
        entt::entity entity =
            m_Scene2D->CreateEntity(TransformComponent(glm::vec3(0.0f), glm::vec3(0.0f), glm::vec3(3.0f)));
        m_Scene2D->AddComponent(entity, SpriteRendererComponent(VAOLibrary::GetInstance().GetVAO("IdentitySquare"),
                                                                glm::vec4(1.0f, 0.7f, 0.8f, 1.0f),
                                                                TextureLibrary::GetInstance().GetTexture("02BG")));
    }

    // Initialize 3D scene
    {
        m_Scene3D = std::make_shared<Scene3D>();
        entt::entity entity = m_Scene3D->CreateEntity(TransformComponent());
        m_Scene3D->AddComponent(entity, MeshRendererComponent(VAOLibrary::GetInstance().GetVAO("IdentityCube"),
                                                              glm::vec4(0.0f, 0.0f, 1.0f, 0.8f)));
    }
};

void MCEngine::EditorLayer::OnEvent(Event &event)
{
    ENGINE_PROFILE_FUNCTION();

    EventDispatcher dispatcher(event);
    dispatcher.Dispatch<KeyEvent>([this](KeyEvent &e) {
        KeyCodeLibrary::GetInstance().SetKeyAction(e.GetKeyCode(), e.GetAction());
        return true;
    });

    m_Scene2D->OnEvent(event);
    m_Scene3D->OnEvent(event);
}

void MCEngine::EditorLayer::OnUpdate(float deltaTime)
{
    ENGINE_PROFILE_FUNCTION();

    // // Switch camera
    // {
    //     if (KeyCodeLibrary::GetInstance().IsKeyDown(ENGINE_KEY_1))
    //     {
    //         m_CameraPtr = m_SceneCameraPtr;
    //     }
    //     if (KeyCodeLibrary::GetInstance().IsKeyDown(ENGINE_KEY_2))
    //     {
    //         m_CameraPtr = m_GameCameraPtr;
    //     }
    // }

    // // Move camera
    // {
    //     if (KeyCodeLibrary::GetInstance().IsKeyDown(ENGINE_KEY_W))
    //     {
    //         m_CameraPtr->SetPosition(m_CameraPtr->GetPosition() + glm::vec3(0.0f, m_CameraMoveSpeed * deltaTime,
    //         0.0f));
    //     }
    //     if (KeyCodeLibrary::GetInstance().IsKeyDown(ENGINE_KEY_S))
    //     {
    //         m_CameraPtr->SetPosition(m_CameraPtr->GetPosition() +
    //                                  glm::vec3(0.0f, -m_CameraMoveSpeed * deltaTime, 0.0f));
    //     }
    //     if (KeyCodeLibrary::GetInstance().IsKeyDown(ENGINE_KEY_A))
    //     {
    //         m_CameraPtr->SetPosition(m_CameraPtr->GetPosition() +
    //                                  glm::vec3(-m_CameraMoveSpeed * deltaTime, 0.0f, 0.0f));
    //     }
    //     if (KeyCodeLibrary::GetInstance().IsKeyDown(ENGINE_KEY_D))
    //     {
    //         m_CameraPtr->SetPosition(m_CameraPtr->GetPosition() + glm::vec3(m_CameraMoveSpeed * deltaTime, 0.0f,
    //         0.0f));
    //     }
    //     if (KeyCodeLibrary::GetInstance().IsKeyDown(ENGINE_KEY_Q))
    //     {
    //         m_CameraPtr->SetPosition(m_CameraPtr->GetPosition() + glm::vec3(0.0f, 0.0f, m_CameraMoveSpeed *
    //         deltaTime));
    //     }
    //     if (KeyCodeLibrary::GetInstance().IsKeyDown(ENGINE_KEY_E))
    //     {
    //         m_CameraPtr->SetPosition(m_CameraPtr->GetPosition() +
    //                                  glm::vec3(0.0f, 0.0f, -m_CameraMoveSpeed * deltaTime));
    //     }
    // }

    // // Rotate camera
    // {
    //     if (KeyCodeLibrary::GetInstance().IsKeyDown(ENGINE_KEY_I))
    //     {
    //         m_CameraPtr->SetRotation(m_CameraPtr->GetRotation() +
    //                                  glm::vec3(-m_CameraRotateSpeed * deltaTime, 0.0f, 0.0f));
    //     }
    //     if (KeyCodeLibrary::GetInstance().IsKeyDown(ENGINE_KEY_K))
    //     {
    //         m_CameraPtr->SetRotation(m_CameraPtr->GetRotation() +
    //                                  glm::vec3(m_CameraRotateSpeed * deltaTime, 0.0f, 0.0f));
    //     }
    //     if (KeyCodeLibrary::GetInstance().IsKeyDown(ENGINE_KEY_J))
    //     {
    //         m_CameraPtr->SetRotation(m_CameraPtr->GetRotation() +
    //                                  glm::vec3(0.0f, -m_CameraRotateSpeed * deltaTime, 0.0f));
    //     }
    //     if (KeyCodeLibrary::GetInstance().IsKeyDown(ENGINE_KEY_L))
    //     {
    //         m_CameraPtr->SetRotation(m_CameraPtr->GetRotation() +
    //                                  glm::vec3(0.0f, m_CameraRotateSpeed * deltaTime, 0.0f));
    //     }
    //     if (KeyCodeLibrary::GetInstance().IsKeyDown(ENGINE_KEY_U))
    //     {
    //         m_CameraPtr->SetRotation(m_CameraPtr->GetRotation() +
    //                                  glm::vec3(0.0f, 0.0f, m_CameraRotateSpeed * deltaTime));
    //     }
    //     if (KeyCodeLibrary::GetInstance().IsKeyDown(ENGINE_KEY_O))
    //     {
    //         m_CameraPtr->SetRotation(m_CameraPtr->GetRotation() +
    //                                  glm::vec3(0.0f, 0.0f, -m_CameraRotateSpeed * deltaTime));
    //     }
    // }

    // // Update camera
    // m_CameraPtr->Update(deltaTime);

    // // Update objects
    // m_Scene2D.Update(deltaTime);
    // m_Scene3D.Update(deltaTime);
}

void MCEngine::EditorLayer::OnRender()
{
    ENGINE_PROFILE_FUNCTION();

    m_Scene2D->Render();
    m_Scene3D->Render();
}