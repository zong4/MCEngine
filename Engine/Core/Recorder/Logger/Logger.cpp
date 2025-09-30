#include "Logger.hpp"

#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/spdlog.h>

std::shared_ptr<spdlog::logger> MCEngine::Logger::s_EngineLoggerPtr = nullptr;
std::shared_ptr<spdlog::logger> MCEngine::Logger::s_EditorLoggerPtr = nullptr;

void MCEngine::Logger::Init(const std::string &dirPath)
{
    if (s_EngineLoggerPtr != nullptr && s_EditorLoggerPtr != nullptr)
        return;

    s_EngineLoggerPtr = CreateLoggerPtr(dirPath, "Engine");
    LOG_ENGINE_INFO("Engine logger initialized");

    s_EditorLoggerPtr = CreateLoggerPtr(dirPath, "Editor");
    LOG_EDITOR_INFO("Editor logger initialized");
}

void MCEngine::Logger::LogEngineTrace(const std::string &message) { s_EngineLoggerPtr->trace(message); }
void MCEngine::Logger::LogEngineInfo(const std::string &message) { s_EngineLoggerPtr->info(message); }
void MCEngine::Logger::LogEngineWarn(const std::string &message) { s_EngineLoggerPtr->warn(message); }
void MCEngine::Logger::LogEngineError(const std::string &message)
{
    s_EngineLoggerPtr->error(message);
    assert(false);
}

void MCEngine::Logger::LogEditorTrace(const std::string &message) { s_EditorLoggerPtr->trace(message); }
void MCEngine::Logger::LogEditorInfo(const std::string &message) { s_EditorLoggerPtr->info(message); }
void MCEngine::Logger::LogEditorWarn(const std::string &message) { s_EditorLoggerPtr->warn(message); }
void MCEngine::Logger::LogEditorError(const std::string &message)
{
    s_EditorLoggerPtr->error(message);
    assert(false);
}

std::shared_ptr<spdlog::logger> MCEngine::Logger::CreateLoggerPtr(const std::string &dirPath, const std::string &name)
{
    // Create console sink and file sink
    auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
    auto file_sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>(dirPath + "/" + name + ".log", true);
    std::vector<spdlog::sink_ptr> sinks{console_sink, file_sink};
    std::shared_ptr<spdlog::logger> loggerPtr = std::make_shared<spdlog::logger>(name, sinks.begin(), sinks.end());

    // Set logger pattern and level
    spdlog::register_logger(loggerPtr);
    loggerPtr->set_pattern("%^[%T] [%n] [thread %t] %v%$");
    loggerPtr->set_level(spdlog::level::trace);
    return loggerPtr;
}