#pragma once

#include "pch.hpp"

#include "Renderer/Material/Material.hpp"

namespace MCEngine
{

class SpriteRendererComponent
{

public:
    SpriteRendererComponent(const std::shared_ptr<VertexArray> &vaoPtr, const glm::vec4 &color,
                            const std::shared_ptr<Texture2D> &texturePtr);

    // Getters
    std::shared_ptr<VertexArray> GetVAOPtr() const { return m_VAOPtr; }
    glm::vec4 &GetColor() { return m_Color; }
    const glm::vec4 &GetColor() const { return m_Color; }
    std::shared_ptr<Texture2D> GetTexturePtr() const { return m_TexturePtr; }

    // Setters
    void SetVAOPtr(const std::shared_ptr<VertexArray> &vaoPtr) { m_VAOPtr = vaoPtr; }
    void SetColor(const glm::vec4 &color) { m_Color = color; }
    void SetTexturePtr(const std::shared_ptr<Texture2D> &texturePtr) { m_TexturePtr = texturePtr; }

private:
    std::shared_ptr<VertexArray> m_VAOPtr;

    // Rendering properties
    glm::vec4 m_Color;
    std::shared_ptr<Texture2D> m_TexturePtr;
};

class MeshRendererComponent
{
public:
    MeshRendererComponent(const std::shared_ptr<VertexArray> &vaoPtr, const std::shared_ptr<Shader> &shaderPtr,
                          const Material &material);

    // Getters
    std::shared_ptr<VertexArray> GetVAOPtr() const { return m_VAOPtr; }
    std::shared_ptr<Shader> GetShaderPtr() const { return m_ShaderPtr; }
    Material &GetMaterial() { return m_Material; }
    const Material &GetMaterial() const { return m_Material; }

    // Setters
    void SetVAOPtr(const std::shared_ptr<VertexArray> &vaoPtr) { m_VAOPtr = vaoPtr; }
    void SetShaderPtr(const std::shared_ptr<Shader> &shaderPtr) { m_ShaderPtr = shaderPtr; }
    void SetMaterial(const Material &material) { m_Material = material; }

private:
    std::shared_ptr<VertexArray> m_VAOPtr;
    std::shared_ptr<Shader> m_ShaderPtr;

    // Rendering properties
    Material m_Material;
};

} // namespace MCEngine