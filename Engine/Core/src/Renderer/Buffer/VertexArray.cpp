#include "VertexArray.hpp"

#include <glad/glad.h>

MCEngine::VertexArray::VertexArray(IndexBuffer &&indexBuffer, VertexBuffer &&vertexBuffer,
                                   const VertexAttribute &attribute)
    : m_VertexBuffer(std::move(vertexBuffer)), m_IndexBuffer(std::move(indexBuffer))
{
    glGenVertexArrays(1, &m_RendererID);
    glBindVertexArray(m_RendererID);

    m_VertexBuffer.Bind();
    m_IndexBuffer.Bind();

    glVertexAttribPointer(attribute.location, attribute.count, attribute.type, attribute.normalized,
                          static_cast<GLsizei>(attribute.stride), attribute.offset);
    glEnableVertexAttribArray(attribute.location);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    m_IndexBuffer.Unbind();
    m_VertexBuffer.Unbind();

    glBindVertexArray(0);

    LOG_ENGINE_INFO("VertexArray created with ID: " + std::to_string(m_RendererID) +
                    ", VertexBuffer ID: " + std::to_string(m_VertexBuffer.GetRendererID()) +
                    ", IndexBuffer ID: " + std::to_string(m_IndexBuffer.GetRendererID()));
}

MCEngine::VertexArray::~VertexArray() { glDeleteVertexArrays(1, &m_RendererID); }

MCEngine::VertexArray::VertexArray(VertexArray &&other)
    : m_RendererID(other.m_RendererID), m_IndexBuffer(std::move(other.m_IndexBuffer)),
      m_VertexBuffer(std::move(other.m_VertexBuffer))
{
    other.m_RendererID = 0;

    LOG_ENGINE_INFO("VertexArray moved with ID: " + std::to_string(m_RendererID));
}

MCEngine::VertexArray &MCEngine::VertexArray::operator=(VertexArray &&other)
{
    if (this != &other)
    {
        glDeleteVertexArrays(1, &m_RendererID);

        m_RendererID = other.m_RendererID;
        m_IndexBuffer = std::move(other.m_IndexBuffer);
        m_VertexBuffer = std::move(other.m_VertexBuffer);

        other.m_RendererID = 0;
    }

    LOG_ENGINE_INFO("VertexArray move-assigned with ID: " + std::to_string(m_RendererID));

    return *this;
}

void MCEngine::VertexArray::Bind() const
{
    glBindVertexArray(m_RendererID);

    m_VertexBuffer.Bind();
    m_IndexBuffer.Bind();
}

void MCEngine::VertexArray::Render() const
{
    glDrawElements(GL_TRIANGLES, m_IndexBuffer.GetCount(), GL_UNSIGNED_INT, 0);
}

void MCEngine::VertexArray::Unbind() const
{
    m_IndexBuffer.Unbind();
    m_VertexBuffer.Unbind();

    glBindVertexArray(0);
}

void MCEngine::VertexArray::SetIndexBuffer(IndexBuffer &&indexBuffer)
{
    Bind();

    m_IndexBuffer = std::move(indexBuffer);
    m_IndexBuffer.Bind();

    GLint error = glGetError();
    if (error != GL_NO_ERROR)
    {
        LOG_ENGINE_ERROR("OpenGL Error: " + std::to_string(error) + " in SetIndexBuffer");
    }

    m_IndexBuffer.Unbind();

    Unbind();

    LOG_ENGINE_INFO("VertexArray ID: " + std::to_string(m_RendererID) +
                    " set with new IndexBuffer ID: " + std::to_string(m_IndexBuffer.GetRendererID()));
}

void MCEngine::VertexArray::SetVertexBuffer(VertexBuffer &&vertexBuffer, const VertexAttribute &attribute)
{
    Bind();

    m_VertexBuffer = std::move(vertexBuffer);
    m_VertexBuffer.Bind();

    GLint error = glGetError();
    if (error != GL_NO_ERROR)
    {
        LOG_ENGINE_ERROR("OpenGL Error: " + std::to_string(error) + " in SetVertexBuffer");
    }

    glVertexAttribPointer(attribute.location, attribute.count, attribute.type, attribute.normalized,
                          static_cast<GLsizei>(attribute.stride), attribute.offset);
    glEnableVertexAttribArray(attribute.location);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    error = glGetError();
    if (error != GL_NO_ERROR)
    {
        LOG_ENGINE_ERROR("OpenGL Error: " + std::to_string(error) + " in SetVertexAttribute");
    }

    m_VertexBuffer.Unbind();
    Unbind();

    LOG_ENGINE_INFO("VertexArray ID: " + std::to_string(m_RendererID) +
                    " set with new VertexBuffer ID: " + std::to_string(m_VertexBuffer.GetRendererID()));
}