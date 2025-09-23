#include "VertexBuffer.hpp"

#include <glad/glad.h>

MCEngine::VertexBuffer::VertexBuffer(const void *data, size_t size)
{
    CreateBuffer(data, size);
}

MCEngine::VertexBuffer::VertexBuffer(const std::vector<float> &vertices)
{
    CreateBuffer(vertices.data(), vertices.size() * sizeof(float));
}

MCEngine::VertexBuffer::~VertexBuffer()
{
    glDeleteBuffers(1, &m_RendererID);
}

MCEngine::VertexBuffer::VertexBuffer(VertexBuffer &&other) noexcept
{
    m_RendererID = other.m_RendererID;
    other.m_RendererID = 0;
}

MCEngine::VertexBuffer &MCEngine::VertexBuffer::operator=(VertexBuffer &&other) noexcept
{
    if (this != &other)
    {
        if (m_RendererID != 0)
        {
            glDeleteBuffers(1, &m_RendererID);
        }

        m_RendererID = other.m_RendererID;
        other.m_RendererID = 0;
    }
    return *this;
}

void MCEngine::VertexBuffer::Bind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
}

void MCEngine::VertexBuffer::Unbind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void MCEngine::VertexBuffer::SetData(const void *data, size_t size)
{
    glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
    glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
}

void MCEngine::VertexBuffer::CreateBuffer(const void *data, size_t size)
{
    glGenBuffers(1, &m_RendererID);
    glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}