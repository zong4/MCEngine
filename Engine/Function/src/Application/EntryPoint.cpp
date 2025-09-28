#include "Application.hpp"

int main()
{
    std::unique_ptr<MCEngine::Application> app;
    {
        MCEngine::Instrumentor::GetInstance().BeginSession(std::string(PROJECT_ROOT) + "/logs/EngineProfile-Init.json");
        MCEngine::Logger::Init(std::string(PROJECT_ROOT) + "/logs");
        app = MCEngine::CreateApplication();
        MCEngine::Instrumentor::GetInstance().EndSession();
    }

    {
        MCEngine::Instrumentor::GetInstance().BeginSession(std::string(PROJECT_ROOT) +
                                                           "/logs/EngineProfile-Runtime.json");
        app->Run();
        MCEngine::Instrumentor::GetInstance().EndSession();
    }

    {
        MCEngine::Instrumentor::GetInstance().BeginSession(std::string(PROJECT_ROOT) +
                                                           "/logs/EngineProfile-Shutdown.json");
        app.reset();
        MCEngine::Instrumentor::GetInstance().EndSession();
    }

    return 0;
}