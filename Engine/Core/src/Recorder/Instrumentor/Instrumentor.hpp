#pragma once

#include <fstream>

namespace MCEngine
{

struct ProfileResult
{
    std::string Name;
    long long Start, End;
    uint32_t ThreadID;
};

class Instrumentor
{
public:
    Instrumentor() = default;
    ~Instrumentor() = default;

    static Instrumentor &Get();

    void BeginSession(const std::string &filepath);
    void EndSession();

    void WriteProfile(const ProfileResult &result);

private:
    std::ofstream m_OutputStream = {};
    int m_ProfileCount = 0;

protected:
    void WriteHeader();
    void WriteFooter();
};

} // namespace MCEngine
