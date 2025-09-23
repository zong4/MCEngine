#pragma once

#include "Object.hpp"

namespace MCEngine
{

struct IdentitySquareData
{
    float vertices[12] = {
        0.5f,  0.5f,  0.0f, // top right
        0.5f,  -0.5f, 0.0f, // bottom right
        -0.5f, -0.5f, 0.0f, // bottom left
        -0.5f, 0.5f,  0.0f  // top left
    };

    unsigned int indices[6] = {
        // note that we start from 0!
        0, 1, 3, // first Triangle
        1, 2, 3  // second Triangle
    };
};

inline const IdentitySquareData g_IdentitySquareData;

class Square : public Object
{
public:
    Square(float size);
    virtual ~Square() override = default;

    Square(const Square &) = delete;
    Square &operator=(const Square &) = delete;
    Square(Square &&);
    Square &operator=(Square &&);

    void Update() override;
    void Render() override;

private:
    float m_size;
    std::unique_ptr<VertexArray> m_VertexArray;

private:
    void SetupSquare();
};

} // namespace MCEngine