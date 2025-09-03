#include "IndexBuffer.hpp"

#include <glad/glad.h>

IndexBuffer::IndexBuffer(const void *data, size_t size)
{
    CreateBuffer(data, size);
}

IndexBuffer::IndexBuffer(const std::vector<uint32_t> &indices)
{
    CreateBuffer(indices.data(), indices.size() * sizeof(uint32_t));
}

IndexBuffer::~IndexBuffer()
{
    glDeleteBuffers(1, &m_RendererID);
}

void IndexBuffer::Bind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
}

void IndexBuffer::Unbind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void IndexBuffer::SetData(const void *data, size_t size)
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
    glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, size, data);
}

void IndexBuffer::CreateBuffer(const void *data, size_t size)
{
    glGenBuffers(1, &m_RendererID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}