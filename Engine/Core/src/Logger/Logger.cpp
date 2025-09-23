#include "Logger.hpp"

#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/spdlog.h>

std::shared_ptr<spdlog::logger> MCEngine::Logger::s_EngineLogger = nullptr;
std::shared_ptr<spdlog::logger> MCEngine::Logger::s_EditorLogger = nullptr;

void MCEngine::Logger::Init()
{
    if (s_EngineLogger != nullptr && s_EditorLogger != nullptr)
        return;

    s_EngineLogger = spdlog::stdout_color_mt("ENGINE");
    s_EngineLogger->set_pattern("%^[%T] [ENGINE] [thread %t] %v%$");
    s_EngineLogger->set_level(spdlog::level::trace);
    s_EngineLogger->info("Engine logger initialized.");

    s_EditorLogger = spdlog::stdout_color_mt("EDITOR");
    s_EditorLogger->set_pattern("%^[%T] [EDITOR] [thread %t] %v%$");
    s_EditorLogger->set_level(spdlog::level::trace);
    s_EditorLogger->info("Editor logger initialized.");
}

void MCEngine::Logger::LogEngineInfo(const std::string &message) { s_EngineLogger->info(message); }
void MCEngine::Logger::LogEngineError(const std::string &message) { s_EngineLogger->error(message); }

void MCEngine::Logger::LogEditorInfo(const std::string &message) { s_EditorLogger->info(message); }
void MCEngine::Logger::LogEditorError(const std::string &message) { s_EditorLogger->error(message); }
