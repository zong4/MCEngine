#pragma once

// #include "Object/Object.hpp"
#include "Library/ShaderLibrary.hpp"
#include "Object/Square.hpp"

namespace MCEngine
{

class Application
{
public:
    Application();
    virtual ~Application() = default;

    void Run();

    void AddObject(Square &&object);

private:
    std::unique_ptr<Window> m_Window = nullptr;
    std::unique_ptr<Square> m_Square = nullptr;
    std::vector<Square> m_Objects;
    std::unique_ptr<ShaderLibrary> m_ShaderLibrary = nullptr;

private:
    void Init();
};

extern std::unique_ptr<Application> CreateApplication();

} // namespace MCEngine