#pragma once

#include <chrono>

namespace MCEngine
{

class Timer
{
public:
    Timer() { Start(); }

    float GetElapsedSeconds() { return GetElapsedTime(); }
    float GetElapsedMilliseconds() { return GetElapsedTime() * 1000.0f; }

protected:
    std::chrono::time_point<std::chrono::high_resolution_clock> m_StartTime;

private:
    void Start();
    float GetElapsedTime();
};

} // namespace MCEngine
