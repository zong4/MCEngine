#pragma once

#include "pch.hpp"

namespace MCEngine
{

class Texture
{
public:
    Texture(int width, int height, void *data);
    Texture(const std::string &path);
    ~Texture();

    unsigned int GetRendererID() const { return m_RendererID; }

public:
    void Bind(unsigned int slot) const;
    void Unbind() const;

    void Resize(int width, int height);

private:
    unsigned int m_RendererID;
    unsigned int m_Format;
};

} // namespace MCEngine