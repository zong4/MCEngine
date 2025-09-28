#pragma once

#include "pch.hpp"

namespace MCEngine
{

class Texture
{
public:
    Texture(void *data, int width, int height);
    Texture(const std::string &path);
    virtual ~Texture();

    unsigned int GetRendererID() const { return m_RendererID; }

    static std::shared_ptr<Texture> GetWhiteTexturePtr();

public:
    void Bind(unsigned int slot) const;
    void Unbind() const;

private:
    unsigned int m_RendererID;
};

} // namespace MCEngine