#include "Application.hpp"

MCEngine::Application::Application(WindowProps props)
{
    MCEngine::Instrumentor::Get().BeginSession(std::string(PROJECT_ROOT) + "/logs/EngineProfile-Setup.json");
    ENGINE_PROFILE_FUNCTION();

    Setup(props);

    MCEngine::Instrumentor::Get().EndSession();
}

MCEngine::Application::~Application()
{
    MCEngine::Instrumentor::Get().BeginSession(std::string(PROJECT_ROOT) + "/logs/EngineProfile-Shutdown.json");
    ENGINE_PROFILE_FUNCTION();

    LOG_ENGINE_INFO("Application terminated.");

    MCEngine::Instrumentor::Get().EndSession();
}

void MCEngine::Application::Run()
{
    MCEngine::Instrumentor::Get().BeginSession(std::string(PROJECT_ROOT) + "/logs/EngineProfile-Runtime.json");
    ENGINE_PROFILE_FUNCTION();

    Timer timer;
    while (!m_Window->ShouldClose())
    {
        m_Window->PreUpdate();
        m_Window->Update(timer.GetElapsedMilliseconds());
        m_Window->PostUpdate();
    }

    MCEngine::Instrumentor::Get().EndSession();
}

void MCEngine::Application::Setup(WindowProps props)
{
    ENGINE_PROFILE_FUNCTION();

    // Init Logger
    MCEngine::Logger::Init(std::string(PROJECT_ROOT) + "/logs");

    // Init Window
    m_Window = std::make_unique<Window>(props);

    LOG_ENGINE_INFO("Application initialized.");
}