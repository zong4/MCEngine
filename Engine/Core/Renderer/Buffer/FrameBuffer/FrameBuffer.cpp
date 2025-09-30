#include "FrameBuffer.hpp"

#include <glad/glad.h>

#define GL_ERROR()                                                                                                     \
    {                                                                                                                  \
        GLint error = glGetError();                                                                                    \
        if (error != GL_NO_ERROR)                                                                                      \
        {                                                                                                              \
            LOG_ENGINE_ERROR("OpenGL Error: " + std::to_string(error) + " in " + std::string(__FUNCTION__));           \
        }                                                                                                              \
    }

MCEngine::FrameBuffer::FrameBuffer(int width, int height, unsigned int renderBufferFormat, int samples)
    : m_Width(width), m_Height(height)
{
    ENGINE_PROFILE_FUNCTION();

    glGenFramebuffers(1, &m_RendererID);
    glBindFramebuffer(GL_FRAMEBUFFER, m_RendererID);

    if (samples == 0)
    {
        m_TexturePtr = std::make_shared<Texture2D>(width, height, nullptr);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_TexturePtr->GetRendererID(), 0);
        GL_ERROR();
    }
    else
    {
        m_TexturePtr = std::make_shared<Texture2D>(width, height, samples);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D_MULTISAMPLE,
                               m_TexturePtr->GetRendererID(), 0);
        GL_ERROR();
    }

    if (renderBufferFormat != 0)
    {
        m_RenderBufferPtr = std::make_shared<RenderBuffer>(width, height, renderBufferFormat, samples);
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER,
                                  m_RenderBufferPtr->GetRendererID());
        GL_ERROR();
    }

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
    {
        LOG_ENGINE_ERROR("FrameBuffer is incomplete!");
    }
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    LOG_ENGINE_INFO("FrameBuffer created with ID: " + std::to_string(m_RendererID) +
                    ", Width: " + std::to_string(width) + ", Height: " + std::to_string(height) +
                    ", RenderBufferFormat: " + std::to_string(renderBufferFormat) +
                    ", Samples: " + std::to_string(samples));
}

MCEngine::FrameBuffer::~FrameBuffer() { glDeleteFramebuffers(1, &m_RendererID); }

void MCEngine::FrameBuffer::Bind() const
{
    glBindFramebuffer(GL_FRAMEBUFFER, m_RendererID);
    GL_ERROR();

    glViewport(0, 0, m_Width, m_Height);
}

void MCEngine::FrameBuffer::Unbind() const
{
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    GL_ERROR();
}

void MCEngine::FrameBuffer::Blit(unsigned int resolveID) const
{
    ENGINE_PROFILE_FUNCTION();

    glBindFramebuffer(GL_READ_FRAMEBUFFER, m_RendererID);
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, resolveID);

    glBlitFramebuffer(0, 0, m_Width, m_Height, 0, 0, m_Width, m_Height, GL_COLOR_BUFFER_BIT, GL_NEAREST);
    GL_ERROR();
}

void MCEngine::FrameBuffer::Resize(int width, int height)
{
    ENGINE_PROFILE_FUNCTION();

    if (width == m_Width && height == m_Height)
        return;

    m_Width = width;
    m_Height = height;
    m_TexturePtr->Resize(width, height);
    if (m_RenderBufferPtr)
    {
        m_RenderBufferPtr->Resize(width, height);
    }

    glBindFramebuffer(GL_FRAMEBUFFER, m_RendererID);
    glViewport(0, 0, m_Width, m_Height);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    GL_ERROR();
}