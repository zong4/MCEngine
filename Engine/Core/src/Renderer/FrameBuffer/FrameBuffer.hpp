#pragma once

#include "RenderBuffer.hpp"
#include "Renderer/Texture/Texture.hpp"

namespace MCEngine
{

class FrameBuffer
{
public:
    FrameBuffer(int width, int height, unsigned int renderBufferFormat = 0);
    ~FrameBuffer();

    FrameBuffer(const FrameBuffer &) = delete;
    FrameBuffer &operator=(const FrameBuffer &) = delete;
    FrameBuffer(FrameBuffer &&) = delete;
    FrameBuffer &operator=(FrameBuffer &&) = delete;

    unsigned int GetRendererID() const { return m_RendererID; }
    int GetWidth() const { return m_Width; }
    int GetHeight() const { return m_Height; }
    std::shared_ptr<Texture> GetTexturePtr() const { return m_TexturePtr; }

public:
    void Bind() const;
    void Unbind() const;
    void Resize(int width, int height);

private:
    unsigned int m_RendererID = 0;
    int m_Width = 0, m_Height = 0;
    std::shared_ptr<Texture> m_TexturePtr = nullptr;
    std::shared_ptr<RenderBuffer> m_RenderBufferPtr = nullptr;
};

} // namespace MCEngine