#include "EditorLayer.hpp"

MCEngine::EditorLayer::EditorLayer() : Layer("EditorLayer")
{
    ENGINE_PROFILE_FUNCTION();

    TransformComponent squareTransform(glm::vec3(0.0f), glm::vec3(0.0f), glm::vec3(3.0f));
    SpriteRendererComponent squareSprite(VAOLibrary::GetInstance().GetVAO("IdentitySquare"),
                                         glm::vec4(1.0f, 0.7f, 0.8f, 1.0f),
                                         TextureLibrary::GetInstance().GetTexture("02BG"));

    TransformComponent cubeTransform(glm::vec3(0.0f), glm::vec3(0.0f), glm::vec3(1.0f));
    MeshRendererComponent cubeMesh(VAOLibrary::GetInstance().GetVAO("IdentityCube"), glm::vec4(0.0f, 0.0f, 1.0f, 0.8f));

    // Initialize 2D scene
    {
        m_Scene2D = std::make_shared<Scene2D>();
        EntityFactory::CreateEntity(m_Scene2D->GetRegistry(), squareTransform, squareSprite);
        EntityFactory::CreateEntity(m_Scene2D->GetRegistry(), cubeTransform, cubeMesh);
    }

    // Initialize 3D scene
    {
        m_Scene3D = std::make_shared<Scene3D>();
        EntityFactory::CreateEntity(m_Scene3D->GetRegistry(), squareTransform, squareSprite);
        EntityFactory::CreateEntity(m_Scene3D->GetRegistry(), cubeTransform, cubeMesh);
    }

    // Set main scene
    m_MainScene = m_Scene3D;
};

void MCEngine::EditorLayer::OnEvent(Event &event)
{
    ENGINE_PROFILE_FUNCTION();

    EventDispatcher dispatcher(event);
    dispatcher.Dispatch<KeyEvent>([this](KeyEvent &e) {
        KeyCodeLibrary::GetInstance().SetKeyAction(e.GetKeyCode(), e.GetAction());
        return true;
    });

    m_MainScene->OnEvent(event);
}

void MCEngine::EditorLayer::OnUpdate(float deltaTime)
{
    ENGINE_PROFILE_FUNCTION();

    // Switch Scene
    {
        if (KeyCodeLibrary::GetInstance().IsKeyDown(ENGINE_KEY_1))
        {
            m_MainScene = m_Scene2D;
        }
        if (KeyCodeLibrary::GetInstance().IsKeyDown(ENGINE_KEY_2))
        {
            m_MainScene = m_Scene3D;
        }
    }

    m_MainScene->Update(deltaTime);
}

void MCEngine::EditorLayer::OnRender()
{
    ENGINE_PROFILE_FUNCTION();

    m_MainScene->Render();
}