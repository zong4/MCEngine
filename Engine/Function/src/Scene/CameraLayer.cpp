#include "CameraLayer.hpp"

#include "Object/Square.hpp"
#include "Renderer/ShaderLibrary.hpp"

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
        auto &&shader = ShaderLibrary::GetInstance().Get("Standard");
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

        // Update camera
        m_Camera->Update(deltaTime);

        // Update objects
        for (const auto &object : m_Objects)
        {
            object->Update(deltaTime);
        }
    }
}