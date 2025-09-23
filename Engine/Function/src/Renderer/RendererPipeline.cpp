#include "RendererPipeline.hpp"

void MCEngine::RendererPipeline::Submit(const std::shared_ptr<Object> &object) { m_Objects.push_back(object); }

void MCEngine::RendererPipeline::Render()
{
    m_Shader->Bind();
    for (const auto &object : m_Objects)
    {
        object->Render();
    }
    m_Shader->Unbind();
}