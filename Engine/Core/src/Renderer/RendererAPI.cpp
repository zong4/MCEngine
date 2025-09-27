#include "RendererAPI.hpp"

MCEngine::RendererAPI &MCEngine::RendererAPI::GetInstanceRef()
{
    static RendererAPI instance;
    return instance;
}

void MCEngine::RendererAPI::DrawQuad(std::shared_ptr<VertexArray> vertexArray)
{
    ENGINE_PROFILE_FUNCTION();

    vertexArray->Render();
}