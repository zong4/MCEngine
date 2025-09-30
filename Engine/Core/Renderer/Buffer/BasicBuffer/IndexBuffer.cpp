#include "IndexBuffer.hpp"

#include <glad/glad.h>

#define GL_ERROR()                                                                                                     \
    {                                                                                                                  \
        GLint error = glGetError();                                                                                    \
        if (error != GL_NO_ERROR)                                                                                      \
        {                                                                                                              \
            LOG_ENGINE_ERROR("OpenGL Error: " + std::to_string(error) + " in " + std::string(__FUNCTION__));           \
        }                                                                                                              \
    }

MCEngine::IndexBuffer::IndexBuffer(const void *data, size_t size)
{
    m_Count = static_cast<int>(size / sizeof(uint32_t));
    CreateBuffer(data, size);
}

MCEngine::IndexBuffer::IndexBuffer(const std::vector<uint32_t> &indices)
{
    m_Count = static_cast<int>(indices.size());
    CreateBuffer(indices.data(), indices.size() * sizeof(uint32_t));
}

MCEngine::IndexBuffer::~IndexBuffer() { glDeleteBuffers(1, &m_RendererID); }

MCEngine::IndexBuffer::IndexBuffer(IndexBuffer &&other)
{
    m_RendererID = other.m_RendererID;
    m_Count = other.m_Count;
    LOG_ENGINE_INFO("IndexBuffer move-assigned with ID: " + std::to_string(m_RendererID) +
                    " and count: " + std::to_string(m_Count));

    // Invalidate the moved-from object
    other.m_RendererID = 0;
}

MCEngine::IndexBuffer &MCEngine::IndexBuffer::operator=(IndexBuffer &&other)
{
    if (this != &other)
    {
        if (m_RendererID != 0)
        {
            glDeleteBuffers(1, &m_RendererID);
        }

        m_RendererID = other.m_RendererID;
        m_Count = other.m_Count;
        LOG_ENGINE_INFO("IndexBuffer move-assigned with ID: " + std::to_string(m_RendererID) +
                        " and count: " + std::to_string(m_Count));

        // Invalidate the moved-from object
        other.m_RendererID = 0;
    }
    return *this;
}

void MCEngine::IndexBuffer::Bind() const { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID); }

void MCEngine::IndexBuffer::Unbind() const { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); }

void MCEngine::IndexBuffer::SetData(const void *data, size_t size)
{
    ENGINE_PROFILE_FUNCTION();

    if (data == nullptr || size == 0)
    {
        LOG_ENGINE_WARN("Invalid IndexBuffer data or size");
        return;
    }

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
    glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, size, data);
    GL_ERROR();

    LOG_ENGINE_INFO("IndexBuffer data updated for ID: " + std::to_string(m_RendererID) +
                    " with new count: " + std::to_string(m_Count));
}

void MCEngine::IndexBuffer::CreateBuffer(const void *data, size_t size)
{
    ENGINE_PROFILE_FUNCTION();

    if (data == nullptr || size == 0)
    {
        LOG_ENGINE_WARN("Invalid IndexBuffer data or size");
        return;
    }

    glGenBuffers(1, &m_RendererID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
    GL_ERROR();

    LOG_ENGINE_INFO("IndexBuffer created with ID: " + std::to_string(m_RendererID) +
                    " and count: " + std::to_string(m_Count));
}