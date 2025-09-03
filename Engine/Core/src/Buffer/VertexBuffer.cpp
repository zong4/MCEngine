#include "VertexBuffer.hpp"

#include <glad/glad.h>

VertexBuffer::VertexBuffer(const void *data, size_t size)
{
    CreateBuffer(data, size);
}

VertexBuffer::VertexBuffer(const std::vector<float> &vertices)
{
    CreateBuffer(vertices.data(), vertices.size() * sizeof(float));
}

VertexBuffer::~VertexBuffer()
{
    glDeleteBuffers(1, &m_RendererID);
}

VertexBuffer::VertexBuffer(VertexBuffer &&other) noexcept
{
    m_RendererID = other.m_RendererID;
    other.m_RendererID = 0;
}

VertexBuffer &VertexBuffer::operator=(VertexBuffer &&other) noexcept
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

void VertexBuffer::Bind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
}

void VertexBuffer::Unbind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VertexBuffer::SetData(const void *data, size_t size)
{
    glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
    glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
}

void VertexBuffer::CreateBuffer(const void *data, size_t size)
{
    glGenBuffers(1, &m_RendererID);
    glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}