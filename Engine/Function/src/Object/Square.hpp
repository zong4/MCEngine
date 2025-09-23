#pragma once

#include "pch.hpp"

class Square
{
public:
    Square(float size);
    virtual ~Square();
    void Draw() const;

private:
    float m_size;
    std::vector<float> m_vertices;
    unsigned int m_VAO, m_VBO;
    void SetupSquare();
};