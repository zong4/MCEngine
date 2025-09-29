#pragma once

#include <chrono>

namespace MCEngine
{

class InstrumentationTimer
{
public:
    InstrumentationTimer(const std::string &name);
    ~InstrumentationTimer();

private:
    std::string m_Name;
    std::chrono::time_point<std::chrono::high_resolution_clock> m_StartTime;
};

#define ENGINE_PROFILE_SCOPE(name) MCEngine::InstrumentationTimer timer##__LINE__(name);
#define ENGINE_PROFILE_FUNCTION() ENGINE_PROFILE_SCOPE(__FUNCTION__)

} // namespace MCEngine