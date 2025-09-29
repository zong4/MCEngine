#include "VertexBuffer.hpp"

#include <glad/glad.h>

#define GL_ERROR()                                                                                                     \
    {                                                                                                                  \
        GLint error = glGetError();                                                                                    \
        if (error != GL_NO_ERROR)                                                                                      \
        {                                                                                                              \
            LOG_ENGINE_ERROR("OpenGL Error: " + std::to_string(error) + " in " + std::string(__FUNCTION__));           \
        }                                                                                                              \
    }

MCEngine::VertexBuffer::VertexBuffer(const void *data, size_t size)
{
    m_Count = static_cast<int>(size / sizeof(float));
    CreateBuffer(data, size);
}

MCEngine::VertexBuffer::VertexBuffer(const std::vector<float> &vertices)
{
    m_Count = static_cast<int>(vertices.size());
    CreateBuffer(vertices.data(), vertices.size() * sizeof(float));
}

MCEngine::VertexBuffer::~VertexBuffer() { glDeleteBuffers(1, &m_RendererID); }

MCEngine::VertexBuffer::VertexBuffer(VertexBuffer &&other)
{
    m_RendererID = other.m_RendererID;
    m_Count = other.m_Count;
    LOG_ENGINE_INFO("VertexBuffer move-assigned with ID: " + std::to_string(m_RendererID) +
                    " and count: " + std::to_string(m_Count));

    // Invalidate the moved-from object
    other.m_RendererID = 0;
}

MCEngine::VertexBuffer &MCEngine::VertexBuffer::operator=(VertexBuffer &&other)
{
    if (this != &other)
    {
        if (m_RendererID != 0)
        {
            glDeleteBuffers(1, &m_RendererID);
        }

        m_RendererID = other.m_RendererID;
        m_Count = other.m_Count;
        LOG_ENGINE_INFO("VertexBuffer move-assigned with ID: " + std::to_string(m_RendererID) +
                        " and count: " + std::to_string(m_Count));

        // Invalidate the moved-from object
        other.m_RendererID = 0;
    }
    return *this;
}

void MCEngine::VertexBuffer::Bind() const { glBindBuffer(GL_ARRAY_BUFFER, m_RendererID); }

void MCEngine::VertexBuffer::Unbind() const { glBindBuffer(GL_ARRAY_BUFFER, 0); }

void MCEngine::VertexBuffer::SetData(const void *data, size_t size)
{
    ENGINE_PROFILE_FUNCTION();

    glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
    glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
    GL_ERROR();

    LOG_ENGINE_INFO("VertexBuffer data updated for ID: " + std::to_string(m_RendererID) +
                    " and count: " + std::to_string(m_Count));
}

void MCEngine::VertexBuffer::CreateBuffer(const void *data, size_t size)
{
    ENGINE_PROFILE_FUNCTION();

    glGenBuffers(1, &m_RendererID);
    glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
    GL_ERROR();

    LOG_ENGINE_INFO("VertexBuffer created with ID: " + std::to_string(m_RendererID) +
                    " and count: " + std::to_string(m_Count));
}