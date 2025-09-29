#pragma once

#include "ECS/Component/Component.hpp"

namespace MCEngine
{

class SpriteRendererComponent : public Component
{

public:
    SpriteRendererComponent(std::shared_ptr<VertexArray> vaoPtr, const glm::vec4 &color,
                            std::shared_ptr<Texture> texturePtr);

    std::shared_ptr<VertexArray> GetVAOPtr() const { return m_VAOPtr; }
    glm::vec4 &GetColor() { return m_Color; }
    const glm::vec4 &GetColor() const { return m_Color; }
    std::shared_ptr<Texture> GetTexturePtr() const { return m_TexturePtr; }

    void SetVAOPtr(std::shared_ptr<VertexArray> vaoPtr) { m_VAOPtr = vaoPtr; }
    void SetColor(const glm::vec4 &color) { m_Color = color; }
    void SetTexturePtr(std::shared_ptr<Texture> texturePtr) { m_TexturePtr = texturePtr; }

    virtual void Update(float deltaTime) override {}

private:
    std::shared_ptr<VertexArray> m_VAOPtr;
    glm::vec4 m_Color;
    std::shared_ptr<Texture> m_TexturePtr;
};

class MeshRendererComponent : public Component
{
public:
    MeshRendererComponent(std::shared_ptr<VertexArray> vaoPtr, const Material &material);

    std::shared_ptr<VertexArray> GetVAOPtr() const { return m_VAOPtr; }
    Material &GetMaterial() { return m_Material; }
    const Material &GetMaterial() const { return m_Material; }

    void SetVAOPtr(std::shared_ptr<VertexArray> vaoPtr) { m_VAOPtr = vaoPtr; }
    void SetMaterial(const Material &material) { m_Material = material; }

    virtual void Update(float deltaTime) override {}

private:
    std::shared_ptr<VertexArray> m_VAOPtr;
    Material m_Material;
};

} // namespace MCEngine