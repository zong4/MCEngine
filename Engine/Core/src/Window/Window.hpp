#pragma once

#include "pch.hpp"

namespace MCEngine
{

class Window
{
public:
    Window(int width, int height, std::string title);
    virtual ~Window();

    void PreUpdate();
    void Update();
    void PostUpdate();

    bool ShouldClose() const;

protected:
    void Init(int width, int height, std::string title);
    void Shutdown();

private:
    void *m_Window = nullptr;
};

} // namespace MCEngine
