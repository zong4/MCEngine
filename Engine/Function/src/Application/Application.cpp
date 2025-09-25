#include "Application.hpp"

void MCEngine::Application::Run()
{
    while (!m_Window->ShouldClose())
    {
        m_Window->PreUpdate();
        m_Window->Update();
        m_Window->PostUpdate();
    }
}

void MCEngine::Application::Init(WindowProps props)
{
    MCEngine::Logger::Init();

    m_Window = std::make_unique<Window>(props);

    LOG_ENGINE_INFO("Application initialized.");
}