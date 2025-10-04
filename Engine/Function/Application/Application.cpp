#include "Application.hpp"

void MCEngine::Application::Run()
{
    ENGINE_PROFILE_FUNCTION();

    Timer timer;
    while (!m_Window->IsRunning())
    {
        float deltaTime = timer.GetElapsedSeconds();
        m_Window->Update(deltaTime);
        m_Window->Render();
    }
}

void MCEngine::Application::Init(const WindowProperty &props)
{
    ENGINE_PROFILE_FUNCTION();

    m_Window = std::make_shared<Window>(props);
    LOG_ENGINE_INFO("Application initialized");
}

void MCEngine::Application::Shutdown()
{
    ENGINE_PROFILE_FUNCTION();

    m_Window.reset();
    LOG_ENGINE_INFO("Application shutdown");
}
