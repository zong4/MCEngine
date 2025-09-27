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

    m_Scene = std::make_shared<Scene>();
    EntityFactory::CreateEntity(m_Scene->GetRegistry(), squareTransform, squareSprite);
    EntityFactory::CreateEntity(m_Scene->GetRegistry(), cubeTransform, cubeMesh);
};

void MCEngine::EditorLayer::OnEvent(Event &event)
{
    ENGINE_PROFILE_FUNCTION();

    EventDispatcher dispatcher(event);
    dispatcher.Dispatch<KeyEvent>([this](KeyEvent &e) {
        KeyCodeLibrary::GetInstance().SetKeyAction(e.GetKeyCode(), e.GetAction());
        return true;
    });

    m_Scene->OnEvent(event);
}

void MCEngine::EditorLayer::OnUpdate(float deltaTime)
{
    ENGINE_PROFILE_FUNCTION();

    m_Scene->Update(deltaTime);
}

void MCEngine::EditorLayer::OnRender()
{
    ENGINE_PROFILE_FUNCTION();

    m_Scene->Render();
}