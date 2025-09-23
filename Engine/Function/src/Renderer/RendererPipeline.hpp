#pragma once

#include "Object/Object.hpp"

namespace MCEngine
{

class RendererPipeline
{
public:
    RendererPipeline(std::shared_ptr<Shader> shader) : m_Shader(shader) {}
    ~RendererPipeline() = default;

    void Submit(const std::shared_ptr<Object> &object);
    void Render();

private:
    std::shared_ptr<Shader> m_Shader;
    std::vector<std::shared_ptr<Object>> m_Objects;
};

} // namespace MCEngine
