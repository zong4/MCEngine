#pragma once

#include "pch.hpp"

class VertexArray;
class Shader;

class Window
{
public:
    Window(int width, int height, std::string title);
    virtual ~Window();

    void Update();
    bool ShouldClose() const;

private:
    void *m_Window = nullptr;

    // todo
    VertexArray *m_VertexArray = nullptr;
    Shader *m_Shader = nullptr;
    unsigned int VAO;
};
