#include "VertexBuffer.hpp"

#include <glad/glad.h>

MCEngine::VertexBuffer::VertexBuffer(const void *data, size_t size) { CreateBuffer(data, size); }

MCEngine::VertexBuffer::VertexBuffer(const std::vector<float> &vertices)
{
    CreateBuffer(vertices.data(), vertices.size() * sizeof(float));
}

MCEngine::VertexBuffer::~VertexBuffer() { glDeleteBuffers(1, &m_RendererID); }

MCEngine::VertexBuffer::VertexBuffer(VertexBuffer &&other) noexcept
{
    m_RendererID = other.m_RendererID;
    other.m_RendererID = 0;

    LOG_ENGINE_INFO("VertexBuffer moved with ID: " + std::to_string(m_RendererID));
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

    LOG_ENGINE_INFO("VertexBuffer move-assigned with ID: " + std::to_string(m_RendererID));

    return *this;
}

void MCEngine::VertexBuffer::Bind() const { glBindBuffer(GL_ARRAY_BUFFER, m_RendererID); }

void MCEngine::VertexBuffer::Unbind() const { glBindBuffer(GL_ARRAY_BUFFER, 0); }

void MCEngine::VertexBuffer::SetData(const void *data, size_t size)
{
    glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
    glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);

    LOG_ENGINE_INFO("VertexBuffer data updated for ID: " + std::to_string(m_RendererID));
}

void MCEngine::VertexBuffer::CreateBuffer(const void *data, size_t size)
{
    glGenBuffers(1, &m_RendererID);
    glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);

    LOG_ENGINE_INFO("VertexBuffer created with ID: " + std::to_string(m_RendererID));
}