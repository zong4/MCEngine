#pragma once

#include "ECS/Component/Component.hpp"

namespace MCEngine
{

class SpriteRendererComponent : public Component
{

public:
    SpriteRendererComponent(std::shared_ptr<VertexArray> vaoPtr, const glm::vec4 &color = glm::vec4(1.0f),
                            std::shared_ptr<Texture> texturePtr = TextureLibrary::GetInstance().GetTexture("White"));

    std::shared_ptr<VertexArray> GetVAOPtr() const { return m_VAOPtr; }
    const glm::vec4 &GetColor() const { return m_Color; }
    std::shared_ptr<Texture> GetTexturePtr() const { return m_TexturePtr; }

    void SetColor(const glm::vec4 &color) { m_Color = color; }
    void SetTexturePtr(std::shared_ptr<Texture> texturePtr) { m_TexturePtr = texturePtr; }

    virtual void Update(float deltaTime) override {}

private:
    std::shared_ptr<VertexArray> m_VAOPtr;

    // Color tint
    glm::vec4 m_Color;
    std::shared_ptr<Texture> m_TexturePtr;
};

class MeshRendererComponent : public Component
{
public:
    MeshRendererComponent(std::shared_ptr<VertexArray> vaoPtr, const glm::vec4 &color = glm::vec4(1.0f));

    std::shared_ptr<VertexArray> GetVAOPtr() const { return m_VAOPtr; }
    const glm::vec4 &GetColor() const { return m_Color; }

    void SetColor(const glm::vec4 &color) { m_Color = color; }

    virtual void Update(float deltaTime) override {}

private:
    std::shared_ptr<VertexArray> m_VAOPtr;

    // Color tint
    glm::vec4 m_Color;
};

} // namespace MCEngine