#include "CameraLayer.hpp"

#include "Object/Square.hpp"

MCEngine::CameraLayer::CameraLayer() : Layer("CameraLayer")
{
    ENGINE_PROFILE_FUNCTION();

    // Initialize cameras
    m_OrthoCamera = std::make_shared<OrthoCamera>(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(8.0f, 6.0f));
    m_PerspectiveCamera =
        std::make_shared<PerspectiveCamera>(glm::vec3(0.0f, 0.0f, 3.0f), 45.0f, 4.0f / 3.0f, 0.1f, 100.0f);
    m_Camera = m_OrthoCamera;

    // Initialize objects
    m_Objects.push_back(Square::GetIdentitySquare());
}

void MCEngine::CameraLayer::OnEvent(Event &event)
{
    ENGINE_PROFILE_FUNCTION();

    // todo Move to other place
    EventDispatcher dispatcher(event);
    dispatcher.Dispatch<KeyEvent>([this](KeyEvent &e) {
        KeyCodeLibrary::GetInstance().SetKeyAction(e.GetKeyCode(), e.GetAction());
        return true;
    });

    m_Camera->OnEvent(event);
    for (const auto &object : m_Objects)
    {
        object->OnEvent(event);
    }
}

void MCEngine::CameraLayer::OnUpdate(float deltaTime)
{
    ENGINE_PROFILE_FUNCTION();

    {
        ENGINE_PROFILE_SCOPE("CameraLayer::RenderObjects");

        // Render objects
        auto &&shader = ShaderLibrary::GetInstance().GetShader("Standard");
        shader->Bind();
        shader->SetUniformMat4("u_View", m_Camera->GetView());
        shader->SetUniformMat4("u_Projection", m_Camera->GetProjection());
        for (const auto &object : m_Objects)
        {
            object->Render("Standard");
        }
    }

    {
        ENGINE_PROFILE_SCOPE("CameraLayer::UpdateObjects");

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
        for (const auto &object : m_Objects)
        {
            object->Update(deltaTime);
        }
    }
}