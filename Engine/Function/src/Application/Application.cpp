#include "Application.hpp"

#include "Scene/CameraLayer.hpp"

void MCEngine::Application::Run()
{
    while (!m_Window->ShouldClose())
    {
        m_Window->PreUpdate();
        m_Window->Update();
        m_Window->PostUpdate();
    }
}

void MCEngine::Application::Init()
{
    MCEngine::Logger::Init();

    m_Window = std::make_unique<Window>(800, 600, "Minecraft Engine");

    AddLayer(std::make_shared<CameraLayer>());

    LOG_ENGINE_INFO("Application initialized.");
}