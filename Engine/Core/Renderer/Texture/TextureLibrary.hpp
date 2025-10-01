#pragma once

#include "Texture2D.hpp"
#include "TextureCube.hpp"

namespace MCEngine
{

class TextureLibrary
{
public:
    static TextureLibrary &GetInstance();

    std::shared_ptr<Texture2D> GetTexture2D(const std::string &name);
    std::shared_ptr<TextureCube> GetTextureCube(const std::string &name);
    void AddTexture(const std::string &name, const std::shared_ptr<Texture> &texturePtr);

private:
    std::unordered_map<std::string, std::shared_ptr<Texture>> m_TextureMap;

private:
    TextureLibrary();
    ~TextureLibrary() = default;

    bool Exists(const std::string &name) const;
};

} // namespace MCEngine