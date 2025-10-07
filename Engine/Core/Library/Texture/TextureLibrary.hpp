#pragma once

#include "Renderer/Texture/Texture2D.hpp"
#include "Renderer/Texture/TextureCube.hpp"

namespace MCEngine
{

class TextureLibrary
{
public:
    static TextureLibrary &GetInstance();

    std::string GetName(const std::shared_ptr<Texture> &texture) const;
    std::shared_ptr<Texture2D> GetTexture2D(const std::string &name);
    std::shared_ptr<TextureCube> GetTextureCube(const std::string &name);
    void AddTexture(const std::string &name, const std::shared_ptr<Texture> &texture);

private:
    std::unordered_map<std::string, std::shared_ptr<Texture>> m_Textures;

private:
    TextureLibrary();
    ~TextureLibrary() = default;

    bool Exists(const std::string &name) const;
};

} // namespace MCEngine