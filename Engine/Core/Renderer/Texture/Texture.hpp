#pragma once

#include "pch.hpp"

namespace MCEngine
{

class Texture2D
{
public:
    Texture2D(int width, int height, void *data);
    Texture2D(int width, int height, int samples);
    Texture2D(const std::string &path);
    ~Texture2D();

    unsigned int GetRendererID() const { return m_RendererID; }

public:
    void Bind(unsigned int slot) const;
    void Unbind() const;

    void Resize(int width, int height);

private:
    unsigned int m_RendererID;
    unsigned int m_Format;
    int m_Samples;
};

class TextureCube
{
public:
    TextureCube(const std::string &directory);
    ~TextureCube();

    unsigned int GetRendererID() const { return m_RendererID; }

public:
    void Bind(unsigned int slot) const;
    void Unbind() const;

private:
    unsigned int m_RendererID = 0;

private:
    void LoadCubemap(const std::array<std::string, 6> &faces);
};

} // namespace MCEngine