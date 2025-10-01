#pragma once

#include "Texture.hpp"

namespace MCEngine
{

class Texture2D : public Texture
{
public:
    Texture2D(int width, int height, void *data);
    Texture2D(int width, int height, int samples);
    Texture2D(int width, int height); // Depth texture
    Texture2D(const std::string &path);
    virtual ~Texture2D() override;

public:
    virtual void Bind(unsigned int slot) const override;
    virtual void Unbind() const override;

    void Resize(int width, int height);

private:
    unsigned int m_Format;
    int m_Samples;
};

} // namespace MCEngine