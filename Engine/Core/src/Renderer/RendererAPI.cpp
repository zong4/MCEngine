#include "RendererAPI.hpp"

#include "Renderer/VertexArray/VAOLibrary.hpp"
#include <glad/glad.h>

MCEngine::RendererAPI &MCEngine::RendererAPI::GetInstance()
{
    static RendererAPI instance;
    return instance;
}

void MCEngine::RendererAPI::DrawQuad(glm::mat4 transform, glm::vec4 color)
{
    ENGINE_PROFILE_FUNCTION();

    auto vertexArray = std::make_shared<VertexArray>(
        MCEngine::IndexBuffer(g_IdentitySquareData.indices, sizeof(g_IdentitySquareData.indices)),
        MCEngine::VertexBuffer(g_IdentitySquareData.vertices, sizeof(g_IdentitySquareData.vertices)),
        MCEngine::VertexAttribute{0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (const void *)0});
    vertexArray->Render();
}