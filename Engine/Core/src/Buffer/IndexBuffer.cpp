#include "IndexBuffer.hpp"

#include <glad/glad.h>

MCEngine::IndexBuffer::IndexBuffer(const void *data, size_t size)
{
    CreateBuffer(data, size);
}

MCEngine::IndexBuffer::IndexBuffer(const std::vector<uint32_t> &indices)
{
    CreateBuffer(indices.data(), indices.size() * sizeof(uint32_t));
}

MCEngine::IndexBuffer::~IndexBuffer()
{
    glDeleteBuffers(1, &m_RendererID);
}

MCEngine::IndexBuffer::IndexBuffer(IndexBuffer &&other) noexcept
{
    m_RendererID = other.m_RendererID;
    other.m_RendererID = 0;
}

MCEngine::IndexBuffer &MCEngine::IndexBuffer::operator=(IndexBuffer &&other) noexcept
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

void MCEngine::IndexBuffer::Bind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
}

void MCEngine::IndexBuffer::Unbind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void MCEngine::IndexBuffer::SetData(const void *data, size_t size)
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
    glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, size, data);
}

void MCEngine::IndexBuffer::CreateBuffer(const void *data, size_t size)
{
    glGenBuffers(1, &m_RendererID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}