#pragma once

#include "pch.hpp"

class GLFWwindow;

class Window
{
public:
    Window(int width, int height, std::string title);
    virtual ~Window();

    void Update();
    bool ShouldClose() const;

private:
    GLFWwindow *m_Window;
};
