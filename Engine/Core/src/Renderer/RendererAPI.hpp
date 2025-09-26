#pragma once

#include "pch.hpp"

namespace MCEngine
{

class RendererAPI
{
public:
    static RendererAPI &GetInstance();

    void DrawQuad(glm::mat4 transform, glm::vec4 color);

private:
    RendererAPI() = default;
    ~RendererAPI() = default;
};

} // namespace MCEngine
