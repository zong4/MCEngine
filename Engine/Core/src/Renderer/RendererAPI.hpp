#pragma once

#include "Renderer/VertexArray/VertexArray.hpp"

namespace MCEngine
{

class RendererAPI
{
public:
    static RendererAPI &GetInstance();

    void DrawQuad(std::shared_ptr<VertexArray> vertexArray);

private:
    RendererAPI() = default;
    ~RendererAPI() = default;
};

} // namespace MCEngine
