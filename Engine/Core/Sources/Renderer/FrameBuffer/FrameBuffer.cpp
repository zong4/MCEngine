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

MCEngine::FrameBuffer::FrameBuffer(int width, int height, unsigned int renderBufferFormat)
    : m_Width(width), m_Height(height)
{
    ENGINE_PROFILE_FUNCTION();

    glGenFramebuffers(1, &m_RendererID);
    glBindFramebuffer(GL_FRAMEBUFFER, m_RendererID);

    m_TexturePtr = std::make_shared<Texture2D>(width, height, nullptr);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_TexturePtr->GetRendererID(), 0);
    GL_ERROR();

    if (renderBufferFormat != 0)
    {
        m_RenderBufferPtr = std::make_shared<RenderBuffer>(width, height, renderBufferFormat);
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
                    ", RenderBufferFormat: " + std::to_string(renderBufferFormat));
}

MCEngine::FrameBuffer::~FrameBuffer() { glDeleteFramebuffers(1, &m_RendererID); }

void MCEngine::FrameBuffer::Bind() const
{
    glBindFramebuffer(GL_FRAMEBUFFER, m_RendererID);
    glViewport(0, 0, m_Width, m_Height);
    GL_ERROR();
}

void MCEngine::FrameBuffer::Unbind() const
{
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    GL_ERROR();
}

void MCEngine::FrameBuffer::Resize(int width, int height)
{
    ENGINE_PROFILE_FUNCTION();

    if (width <= 0 || height <= 0)
    {
        LOG_ENGINE_WARN("Attempted to resize FrameBuffer to invalid size: " + std::to_string(width) + "x" +
                        std::to_string(height));
        return;
    }

    if (width == m_Width && height == m_Height)
    {
        return;
    }

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

    LOG_ENGINE_TRACE("FrameBuffer resized to Width: " + std::to_string(width) + ", Height: " + std::to_string(height));
}