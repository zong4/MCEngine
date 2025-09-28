#pragma once

#include "pch.hpp"

namespace MCEngine
{

class Texture
{
public:
    Texture(void *data, int width, int height);
    Texture(const std::string &path);
    ~Texture();

    unsigned int GetRendererID() const { return m_RendererID; }

public:
    void Bind(unsigned int slot) const;
    void Unbind() const;

private:
    unsigned int m_RendererID;
};

} // namespace MCEngine