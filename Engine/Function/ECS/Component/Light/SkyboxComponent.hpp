#pragma once

#include "pch.hpp"

namespace MCEngine
{

class SkyboxComponent
{
public:
    SkyboxComponent(
        const std::shared_ptr<TextureCube> &textureCube = MCEngine::TextureLibrary::GetInstance().GetTextureCube("3"))
        : m_TextureCube(textureCube)
    {
        LOG_ENGINE_TRACE("Skybox Component created");
    }

    // Getters
    std::shared_ptr<TextureCube> &GetTextureCube() { return m_TextureCube; }
    const std::shared_ptr<TextureCube> &GetTextureCube() const { return m_TextureCube; }

    // Setters
    void SetTextureCube(const std::shared_ptr<TextureCube> &textureCube) { m_TextureCube = textureCube; }

private:
    std::shared_ptr<TextureCube> m_TextureCube;
};

} // namespace MCEngine