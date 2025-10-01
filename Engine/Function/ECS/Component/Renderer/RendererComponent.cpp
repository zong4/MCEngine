#include "RendererComponent.hpp"

MCEngine::SpriteRendererComponent::SpriteRendererComponent(const std::shared_ptr<VertexArray> &vaoPtr,
                                                           const glm::vec4 &color,
                                                           const std::shared_ptr<Texture2D> &texturePtr)
    : m_VAOPtr(vaoPtr), m_Color(color), m_TexturePtr(texturePtr)
{
    LOG_ENGINE_INFO(
        "SpriteRendererComponent created with RendererID: " + std::to_string((uint32_t)m_VAOPtr->GetRendererID()) +
        ", color: " + ToString(m_Color) + ", textureID: " + std::to_string((uint32_t)m_TexturePtr->GetRendererID()));
}

MCEngine::MeshRendererComponent::MeshRendererComponent(const std::shared_ptr<VertexArray> &vaoPtr,
                                                       const std::shared_ptr<Shader> &shaderPtr,
                                                       const Material &material)
    : m_VAOPtr(vaoPtr), m_ShaderPtr(shaderPtr), m_Material(material)
{
    LOG_ENGINE_INFO(
        "MeshRendererComponent created with RendererID: " + std::to_string((uint32_t)m_VAOPtr->GetRendererID()) +
        ", ShaderID: " + std::to_string((uint32_t)m_ShaderPtr->GetRendererID()) + ", " + m_Material.ToString());
}