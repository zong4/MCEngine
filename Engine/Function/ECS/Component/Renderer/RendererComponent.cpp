#include "RendererComponent.hpp"

MCEngine::SpriteRendererComponent::SpriteRendererComponent(const std::shared_ptr<VertexArray> &vao,
                                                           const glm::vec4 &color,
                                                           const std::shared_ptr<Texture2D> &texture)
    : m_VAO(vao), m_Color(color), m_Texture(texture)
{
    LOG_ENGINE_TRACE(
        "SpriteRendererComponent created with RendererID: " + std::to_string((uint32_t)m_VAO->GetRendererID()) +
        ", color: " + ToString(m_Color) + ", textureID: " + std::to_string((uint32_t)m_Texture->GetRendererID()));
}

MCEngine::MeshRendererComponent::MeshRendererComponent(const std::shared_ptr<Shader> &shader, const Material &material)
    : m_Shader(shader), m_Material(material)
{
    LOG_ENGINE_TRACE("MeshRendererComponent created with ShaderID: " +
                     std::to_string((uint32_t)m_Shader->GetRendererID()) + ", " + m_Material.ToString());
}