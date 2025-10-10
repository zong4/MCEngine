#pragma once

#include "pch.hpp"

namespace MCEngine
{

class SkyboxComponent
{
public:
    SkyboxComponent(const std::string textureCubeName = "3") : m_TextureCubeName(textureCubeName) {}

    // Getters
    const std::string &GetTextureCubeName() const { return m_TextureCubeName; }
    std::shared_ptr<TextureCube> GetTextureCube() const
    {
        return MCEngine::TextureLibrary::GetInstance().GetTextureCube(m_TextureCubeName);
    }

    // Setters
    void SetTextureCubeName(const std::string &textureCubeName) { m_TextureCubeName = textureCubeName; }

private:
    std::string m_TextureCubeName;
};

} // namespace MCEngine