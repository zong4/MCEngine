#pragma once

#include "pch.hpp"

namespace MCEngine
{

class SkyboxComponent
{
public:
    SkyboxComponent(const std::shared_ptr<TextureCube> &textureCube);

    // Getters
    std::shared_ptr<TextureCube> &GetTextureCubePtr() { return m_TextureCubePtr; }
    const std::shared_ptr<TextureCube> &GetTextureCubePtr() const { return m_TextureCubePtr; }

    // Setters
    void SetTextureCube(const std::shared_ptr<TextureCube> &textureCube) { m_TextureCubePtr = textureCube; }

private:
    std::shared_ptr<TextureCube> m_TextureCubePtr;
};

} // namespace MCEngine