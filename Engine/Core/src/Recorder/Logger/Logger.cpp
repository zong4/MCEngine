#include "Logger.hpp"

#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/spdlog.h>

std::shared_ptr<spdlog::logger> MCEngine::Logger::s_EngineLoggerPtr = nullptr;
std::shared_ptr<spdlog::logger> MCEngine::Logger::s_EditorLoggerPtr = nullptr;

void MCEngine::Logger::Init(std::string dirPath)
{
    if (s_EngineLoggerPtr != nullptr && s_EditorLoggerPtr != nullptr)
        return;

    {
        auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
        auto file_sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>(dirPath + "/Engine.log", true);

        std::vector<spdlog::sink_ptr> sinks{console_sink, file_sink};
        s_EngineLoggerPtr = std::make_shared<spdlog::logger>("Engine", sinks.begin(), sinks.end());

        spdlog::register_logger(s_EngineLoggerPtr);
        s_EngineLoggerPtr->set_pattern("%^[%T] [Engine] [thread %t] %v%$");
        s_EngineLoggerPtr->set_level(spdlog::level::trace);
        LOG_ENGINE_INFO("Engine logger initialized.");
    }

    {
        auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
        auto file_sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>(dirPath + "/Editor.log", true);

        std::vector<spdlog::sink_ptr> sinks{console_sink, file_sink};
        s_EditorLoggerPtr = std::make_shared<spdlog::logger>("Editor", sinks.begin(), sinks.end());

        spdlog::register_logger(s_EditorLoggerPtr);
        s_EditorLoggerPtr->set_pattern("%^[%T] [Editor] [thread %t] %v%$");
        s_EditorLoggerPtr->set_level(spdlog::level::trace);
        LOG_EDITOR_INFO("Editor logger initialized.");
    }
}

void MCEngine::Logger::LogEngineTrace(const std::string &message) { s_EngineLoggerPtr->trace(message); }
void MCEngine::Logger::LogEngineInfo(const std::string &message) { s_EngineLoggerPtr->info(message); }
void MCEngine::Logger::LogEngineWarn(const std::string &message) { s_EngineLoggerPtr->warn(message); }
void MCEngine::Logger::LogEngineError(const std::string &message) { s_EngineLoggerPtr->error(message); }

void MCEngine::Logger::LogEditorTrace(const std::string &message) { s_EditorLoggerPtr->trace(message); }
void MCEngine::Logger::LogEditorInfo(const std::string &message) { s_EditorLoggerPtr->info(message); }
void MCEngine::Logger::LogEditorWarn(const std::string &message) { s_EditorLoggerPtr->warn(message); }
void MCEngine::Logger::LogEditorError(const std::string &message) { s_EditorLoggerPtr->error(message); }