#pragma once

#include "Texture.hpp"

namespace MCEngine
{

class Texture2DLibrary
{
public:
    static Texture2DLibrary &GetInstance();

    std::shared_ptr<Texture2D> GetTexture(const std::string &name);
    void AddTexture(const std::string &name, const std::shared_ptr<Texture2D> &texturePtr);

private:
    std::unordered_map<std::string, std::shared_ptr<Texture2D>> m_TextureMap;

private:
    Texture2DLibrary();
    ~Texture2DLibrary() = default;

    bool Exists(const std::string &name) const;
};

} // namespace MCEngine