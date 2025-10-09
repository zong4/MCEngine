#pragma once

#include "pch.hpp"

#include "Renderer/Material/Material.hpp"

namespace MCEngine
{

class SpriteRendererComponent
{

public:
    SpriteRendererComponent(
        const std::shared_ptr<VertexArray> &vao = VAOLibrary::GetInstance().GetVAO("Square"),
        const glm::vec4 &color = glm::vec4(1.0f),
        const std::shared_ptr<Texture2D> &texture = TextureLibrary::GetInstance().GetTexture2D("White"));

    // Getters
    std::shared_ptr<VertexArray> GetVAO() const { return m_VAO; }
    glm::vec4 &GetColor() { return m_Color; }
    const glm::vec4 &GetColor() const { return m_Color; }
    std::shared_ptr<Texture2D> GetTexture() const { return m_Texture; }

    // Setters
    void SetVAO(const std::shared_ptr<VertexArray> &vao) { m_VAO = vao; }
    void SetColor(const glm::vec4 &color) { m_Color = color; }
    void SetTexture(const std::shared_ptr<Texture2D> &texture) { m_Texture = texture; }

private:
    std::shared_ptr<VertexArray> m_VAO;
    glm::vec4 m_Color;
    std::shared_ptr<Texture2D> m_Texture;
};

class MeshRendererComponent
{
public:
    MeshRendererComponent(const Material &material = Material(glm::vec4(1.0f), 0.3f, 1.0f, 0.5f, 32.0f));

    Material &GetMaterial() { return m_Material; }
    const Material &GetMaterial() const { return m_Material; }
    void SetMaterial(const Material &material) { m_Material = material; }

private:
    Material m_Material;
};

} // namespace MCEngine