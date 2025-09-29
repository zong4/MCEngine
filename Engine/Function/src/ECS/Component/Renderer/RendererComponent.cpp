#include "RendererComponent.hpp"

MCEngine::SpriteRendererComponent::SpriteRendererComponent(std::shared_ptr<VertexArray> vaoPtr, const glm::vec4 &color,
                                                           std::shared_ptr<Texture> texturePtr)
    : m_VAOPtr(vaoPtr), m_Color(color), m_TexturePtr(texturePtr)
{
    LOG_ENGINE_INFO(
        "SpriteRendererComponent created with RendererID: " + std::to_string((uint32_t)m_VAOPtr->GetRendererID()) +
        ", color: " + ToString(m_Color) + ", textureID: " + std::to_string((uint32_t)m_TexturePtr->GetRendererID()));
}

MCEngine::MeshRendererComponent::MeshRendererComponent(std::shared_ptr<VertexArray> vaoPtr, const Material &material)
    : m_VAOPtr(vaoPtr), m_Material(material)
{
    LOG_ENGINE_INFO("MeshRendererComponent created with RendererID: " +
                    std::to_string((uint32_t)m_VAOPtr->GetRendererID()) + ", Material: " + m_Material.ToString());
}