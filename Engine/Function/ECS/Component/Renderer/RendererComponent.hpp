#pragma once

#include "pch.hpp"

#include "Renderer/Material/Material.hpp"

namespace MCEngine
{

class SpriteRendererComponent
{

public:
    SpriteRendererComponent(
        const glm::vec4 &color = glm::vec4(1.0f),
        const std::shared_ptr<Texture2D> &texture = TextureLibrary::GetInstance().GetTexture2D("White"))
        : m_Color(color), m_Texture(texture)
    {
    }

    // Getters
    glm::vec4 &GetColor() { return m_Color; }
    const glm::vec4 &GetColor() const { return m_Color; }
    std::shared_ptr<Texture2D> GetTexture() const { return m_Texture; }

    // Setters
    void SetColor(const glm::vec4 &color) { m_Color = color; }
    void SetTexture(const std::shared_ptr<Texture2D> &texture) { m_Texture = texture; }

private:
    glm::vec4 m_Color;
    std::shared_ptr<Texture2D> m_Texture;
};

class MeshRendererComponent
{
public:
    MeshRendererComponent(const Material &material = Material(glm::vec4(1.0f), 0.3f, 1.0f, 0.5f, 32.0f))
        : m_Material(material)
    {
    }

    Material &GetMaterial() { return m_Material; }
    const Material &GetMaterial() const { return m_Material; }
    void SetMaterial(const Material &material) { m_Material = material; }

private:
    Material m_Material;
};

} // namespace MCEngine