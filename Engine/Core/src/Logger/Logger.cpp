#include "Logger.hpp"

#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/spdlog.h>

std::shared_ptr<spdlog::logger> MCEngine::Logger::s_EngineLogger = nullptr;
std::shared_ptr<spdlog::logger> MCEngine::Logger::s_EditorLogger = nullptr;

void MCEngine::Logger::Init()
{
    if (s_EngineLogger != nullptr && s_EditorLogger != nullptr)
        return;

    {
        auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
        auto file_sink =
            std::make_shared<spdlog::sinks::basic_file_sink_mt>(std::string(PROJECT_ROOT) + "/Logs/Engine.log", true);

        std::vector<spdlog::sink_ptr> sinks{console_sink, file_sink};
        s_EngineLogger = std::make_shared<spdlog::logger>("ENGINE", sinks.begin(), sinks.end());

        spdlog::register_logger(s_EngineLogger);
        s_EngineLogger->set_pattern("%^[%T] [ENGINE] [thread %t] %v%$");
        s_EngineLogger->set_level(spdlog::level::trace);
        LOG_ENGINE_INFO("Engine logger initialized.");
    }

    {
        auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
        auto file_sink =
            std::make_shared<spdlog::sinks::basic_file_sink_mt>(std::string(PROJECT_ROOT) + "/Logs/Editor.log", true);

        std::vector<spdlog::sink_ptr> sinks{console_sink, file_sink};
        s_EditorLogger = std::make_shared<spdlog::logger>("EDITOR", sinks.begin(), sinks.end());

        spdlog::register_logger(s_EditorLogger);
        s_EditorLogger->set_pattern("%^[%T] [EDITOR] [thread %t] %v%$");
        s_EditorLogger->set_level(spdlog::level::trace);
        LOG_EDITOR_INFO("Editor logger initialized.");
    }
}

void MCEngine::Logger::LogEngineTrace(const std::string &message) { s_EngineLogger->trace(message); }
void MCEngine::Logger::LogEngineInfo(const std::string &message) { s_EngineLogger->info(message); }
void MCEngine::Logger::LogEngineError(const std::string &message) { s_EngineLogger->error(message); }

void MCEngine::Logger::LogEditorInfo(const std::string &message) { s_EditorLogger->info(message); }
void MCEngine::Logger::LogEditorError(const std::string &message) { s_EditorLogger->error(message); }
