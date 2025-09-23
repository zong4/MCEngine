#include "Square.hpp"

MCEngine::Square::Square(float size) : Object(), m_size(size)
{
    SetupSquare();
}

MCEngine::Square::Square(Square &&other) : m_size(other.m_size), m_VertexArray(std::move(other.m_VertexArray))
{
}

MCEngine::Square &MCEngine::Square::operator=(Square &&other)
{
    if (this != &other)
    {
        m_size = other.m_size;
        m_VertexArray = std::move(other.m_VertexArray);
    }
    return *this;
}

void MCEngine::Square::Update()
{
    // Update logic for the square (if any)
}

void MCEngine::Square::Render()
{
    m_VertexArray->Bind();
    m_VertexArray->Render();
    m_VertexArray->Unbind();
}

void MCEngine::Square::SetupSquare()
{
    m_VertexArray = std::make_unique<VertexArray>();

    m_VertexArray->AddVertexBuffer(
        std::move(VertexBuffer(g_IdentitySquareData.vertices, sizeof(g_IdentitySquareData.vertices))),
        {0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0});
    m_VertexArray->SetIndexBuffer(IndexBuffer(g_IdentitySquareData.indices, sizeof(g_IdentitySquareData.indices)));
}