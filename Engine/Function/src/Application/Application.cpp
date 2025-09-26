#include "Application.hpp"

void MCEngine::Application::Run()
{
    ENGINE_PROFILE_FUNCTION();

    Timer timer;
    while (!m_Window->ShouldClose())
    {
        m_Window->PreUpdate();
        m_Window->Update(timer.GetElapsedSeconds());
        m_Window->PostUpdate();
    }
}

void MCEngine::Application::Init(WindowProps props)
{
    ENGINE_PROFILE_FUNCTION();

    m_Window = std::make_shared<Window>(props);

    LOG_ENGINE_INFO("Application initialized.");
}

void MCEngine::Application::Shutdown()
{
    ENGINE_PROFILE_FUNCTION();

    m_Window.reset();

    LOG_ENGINE_INFO("Application shutdown.");
}
