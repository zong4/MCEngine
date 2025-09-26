#pragma once

#include "Timer.hpp"

namespace MCEngine
{

class InstrumentationTimer : public Timer
{
public:
    InstrumentationTimer(const std::string &name);
    ~InstrumentationTimer();

private:
    std::string m_Name;
};

#define ENGINE_PROFILE_SCOPE(name) MCEngine::InstrumentationTimer timer##__LINE__(name);
#define ENGINE_PROFILE_FUNCTION() ENGINE_PROFILE_SCOPE(__FUNCTION__)

} // namespace MCEngine