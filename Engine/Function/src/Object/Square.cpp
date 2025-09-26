#include "Square.hpp"

MCEngine::Square::Square(float size) : Object(), m_size(size) { SetupSquare(); }

void MCEngine::Square::Update(float deltaTime) {}

void MCEngine::Square::SetupSquare()
{
    m_VertexArray = std::make_shared<VertexArray>(
        MCEngine::IndexBuffer(g_IdentitySquareData.indices, sizeof(g_IdentitySquareData.indices)),
        MCEngine::VertexBuffer(g_IdentitySquareData.vertices, sizeof(g_IdentitySquareData.vertices)),
        MCEngine::VertexAttribute{0, 3, ENGINE_FLOAT, ENGINE_FALSE, 3 * sizeof(float), (const void *)0});

    LOG_ENGINE_INFO("Square object created with size: " + std::to_string(m_size));
}

std::shared_ptr<MCEngine::Square> &MCEngine::Square::GetIdentitySquare()
{
    static std::shared_ptr<Square> identitySquare = std::make_shared<Square>(1.0f);
    return identitySquare;
}