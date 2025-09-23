#pragma once

#include <memory>
#include <string>

namespace spdlog
{
class logger; // forward declaration
}

namespace MCEngine
{

class Logger
{
public:
    static void Init();

    static void LogEngineInfo(const std::string &message);
    static void LogEngineError(const std::string &message);

    static void LogEditorInfo(const std::string &message);
    static void LogEditorError(const std::string &message);

    static std::shared_ptr<spdlog::logger> s_EngineLogger;
    static std::shared_ptr<spdlog::logger> s_EditorLogger;
};

#ifdef DEBUG

#define LOG_ENGINE_INFO(msg) MCEngine::Logger::LogEngineInfo(msg)
#define LOG_ENGINE_ERROR(msg) MCEngine::Logger::LogEngineError(msg)

#define LOG_EDITOR_INFO(msg) MCEngine::Logger::LogEditorInfo(msg)
#define LOG_EDITOR_ERROR(msg) MCEngine::Logger::LogEditorError(msg)

#else

#define LOG_ENGINE_INFO(msg)
#define LOG_ENGINE_ERROR(msg)

#define LOG_EDITOR_INFO(msg)
#define LOG_EDITOR_ERROR(msg)

#endif

} // namespace MCEngine