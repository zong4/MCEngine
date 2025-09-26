#include "VertexArray.hpp"

#include <glad/glad.h>

MCEngine::VertexArray::VertexArray(IndexBuffer &&indexBuffer, VertexBuffer &&vertexBuffer,
                                   const VertexAttribute &attribute)
    : m_VertexBuffer(std::move(vertexBuffer)), m_IndexBuffer(std::move(indexBuffer))
{
    ENGINE_PROFILE_FUNCTION();

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
    LOG_ENGINE_INFO("VertexArray moved with ID: " + std::to_string(m_RendererID));

    // Invalidate the moved-from object
    other.m_RendererID = 0;
}

MCEngine::VertexArray &MCEngine::VertexArray::operator=(VertexArray &&other)
{
    if (this != &other)
    {
        glDeleteVertexArrays(1, &m_RendererID);

        m_RendererID = other.m_RendererID;
        m_IndexBuffer = std::move(other.m_IndexBuffer);
        m_VertexBuffer = std::move(other.m_VertexBuffer);
        LOG_ENGINE_INFO("VertexArray move-assigned with ID: " + std::to_string(m_RendererID));

        // Invalidate the moved-from object
        other.m_RendererID = 0;
    }
    return *this;
}

void MCEngine::VertexArray::SetIndexBuffer(IndexBuffer &&indexBuffer)
{
    ENGINE_PROFILE_FUNCTION();

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
    ENGINE_PROFILE_FUNCTION();

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

void MCEngine::VertexArray::Render() const
{
    ENGINE_PROFILE_FUNCTION();

    Bind();
    m_VertexBuffer.Bind();
    m_IndexBuffer.Bind();
    glDrawElements(GL_TRIANGLES, m_IndexBuffer.GetCount(), GL_UNSIGNED_INT, 0);
    m_IndexBuffer.Unbind();
    m_VertexBuffer.Unbind();
    Unbind();
}

void MCEngine::VertexArray::Bind() const { glBindVertexArray(m_RendererID); }

void MCEngine::VertexArray::Unbind() const { glBindVertexArray(0); }