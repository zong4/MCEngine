#include "CameraLayer.hpp"

#include "Object/Square.hpp"
#include "Renderer/ShaderLibrary.hpp"

MCEngine::CameraLayer::CameraLayer() : Layer("CameraLayer")
{
    m_Camera = std::make_shared<OrthoCamera>(glm::vec3(0.5f, 0.0f, 0.0f), glm::vec2(8.0f, 6.0f));

    m_Objects.push_back(Square::GetIdentitySquare());
}

void MCEngine::CameraLayer::OnEvent(Event &event)
{
    EventDispatcher dispatcher(event);
    dispatcher.Dispatch<KeyEvent>([this](KeyEvent &e) {
        if (e.GetAction() == 1 || e.GetAction() == 2)
        {
            switch (e.GetKeyCode())
            {
            case ENGINE_KEY_W:
                m_Camera->SetPosition(m_Camera->GetPosition() + glm::vec3(0.0f, m_CameraMoveSpeed, 0.0f));
                return true;
            case ENGINE_KEY_S:
                m_Camera->SetPosition(m_Camera->GetPosition() - glm::vec3(0.0f, m_CameraMoveSpeed, 0.0f));
                return true;
            case ENGINE_KEY_A:
                m_Camera->SetPosition(m_Camera->GetPosition() - glm::vec3(m_CameraMoveSpeed, 0.0f, 0.0f));
                return true;
            case ENGINE_KEY_D:
                m_Camera->SetPosition(m_Camera->GetPosition() + glm::vec3(m_CameraMoveSpeed, 0.0f, 0.0f));
                return true;
            default:
                break;
            }
        }

        return false;
    });
}

void MCEngine::CameraLayer::OnUpdate()
{
    auto &&shader = ShaderLibrary::GetInstance().Get("Standard");

    shader->Bind();

    shader->SetUniformMat4("u_View", m_Camera->GetView());
    shader->SetUniformMat4("u_Projection", m_Camera->GetProjection());

    for (const auto &object : m_Objects)
    {
        object->Render("Standard");
    }

    for (const auto &object : m_Objects)
    {
        object->Update();
    }
}