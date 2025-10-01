#pragma once

#include "RenderBuffer.hpp"
#include "Renderer/Texture/Texture2D.hpp"

namespace MCEngine
{

enum class FrameBufferType
{
    Color,
    Depth,
    MultiSample,
};

class FrameBuffer
{
public:
    FrameBuffer(FrameBufferType type, int width, int height, int samples = 0);
    ~FrameBuffer();

    FrameBuffer(const FrameBuffer &) = delete;
    FrameBuffer &operator=(const FrameBuffer &) = delete;
    FrameBuffer(FrameBuffer &&) = delete;
    FrameBuffer &operator=(FrameBuffer &&) = delete;

    // Getters
    unsigned int GetRendererID() const { return m_RendererID; }
    int GetWidth() const { return m_Width; }
    int GetHeight() const { return m_Height; }
    std::shared_ptr<Texture2D> GetTexturePtr() const { return m_TexturePtr; }

public:
    void Bind() const;
    void Unbind() const;
    void Blit(unsigned int resolveID) const;
    void Resize(int width, int height);

private:
    FrameBufferType m_Type;
    unsigned int m_RendererID = 0;
    int m_Width, m_Height;
    std::shared_ptr<Texture2D> m_TexturePtr = nullptr;
    std::shared_ptr<RenderBuffer> m_RenderBufferPtr = nullptr;

private:
    void BindBasicTexture(int width, int height);
    void BindMultiSampleTexture(int width, int height, int samples);

    void BindRenderBuffer(int width, int height, unsigned int internalFormat, int samples);
};

} // namespace MCEngine