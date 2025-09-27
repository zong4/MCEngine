#pragma once

#include "ECS/Component/Component.hpp"

namespace MCEngine
{

struct SpriteRendererComponent : public Component
{
    std::shared_ptr<VertexArray> VAOPtr;

    // Color tint
    glm::vec4 Color;
    std::shared_ptr<Texture> TexturePtr;

public:
    SpriteRendererComponent(std::shared_ptr<VertexArray> vaoPtr, glm::vec4 color = glm::vec4(1.0f),
                            std::shared_ptr<Texture> texturePtr = Texture::GetWhiteTexturePtr())
        : VAOPtr(vaoPtr), Color(color), TexturePtr(texturePtr)
    {
    }
};

struct MeshRendererComponent : public Component
{
    std::shared_ptr<VertexArray> VAOPtr;

    // Color tint
    glm::vec4 Color;

public:
    MeshRendererComponent(std::shared_ptr<VertexArray> vaoPtr, glm::vec4 color = glm::vec4(1.0f))
        : VAOPtr(vaoPtr), Color(color)
    {
    }
};

} // namespace MCEngine