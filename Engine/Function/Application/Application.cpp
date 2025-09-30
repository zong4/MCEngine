#include "Application.hpp"

void MCEngine::Application::Run()
{
    ENGINE_PROFILE_FUNCTION();

    Timer timer;
    while (!m_WindowPtr->IsRunning())
    {
        float deltaTime = timer.GetElapsedSeconds();
        m_WindowPtr->Update(deltaTime);
        m_WindowPtr->Render(deltaTime);
    }
}

void MCEngine::Application::Init(const WindowProperty &props)
{
    ENGINE_PROFILE_FUNCTION();

    m_WindowPtr = std::make_shared<Window>(props);

    LOG_ENGINE_INFO("Application initialized");
}

void MCEngine::Application::Shutdown()
{
    ENGINE_PROFILE_FUNCTION();

    m_WindowPtr.reset();

    LOG_ENGINE_INFO("Application shutdown");
}
