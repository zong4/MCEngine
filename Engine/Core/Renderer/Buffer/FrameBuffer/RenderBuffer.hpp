#pragma once

#include "pch.hpp"

namespace MCEngine
{

class RenderBuffer
{
public:
    RenderBuffer(int width, int height, unsigned int internalFormat = 0, int samples = 0); // GL_DEPTH24_STENCIL8
    ~RenderBuffer();

    RenderBuffer(const RenderBuffer &) = delete;
    RenderBuffer &operator=(const RenderBuffer &) = delete;
    RenderBuffer(RenderBuffer &&) = delete;
    RenderBuffer &operator=(RenderBuffer &&) = delete;

    unsigned int GetRendererID() const { return m_RendererID; }

public:
    void Resize(int width, int height);

private:
    unsigned int m_RendererID = 0;
    int m_Samples;
    unsigned int m_InternalFormat;

private:
    void Bind(int width, int height) const;
    void Unbind() const;
};

} // namespace MCEngine