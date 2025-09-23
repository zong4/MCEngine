#include "VertexArray.hpp"

#include <glad/glad.h>

MCEngine::VertexArray::VertexArray()
{
    glGenVertexArrays(1, &m_RendererID);
}

MCEngine::VertexArray::~VertexArray()
{
    glDeleteVertexArrays(1, &m_RendererID);
}

MCEngine::VertexArray::VertexArray(VertexArray &&other)
    : m_RendererID(other.m_RendererID), m_IndexBuffer(std::move(other.m_IndexBuffer)),
      m_VertexBuffers(std::move(other.m_VertexBuffers)), m_VertexAttributes(std::move(other.m_VertexAttributes))
{
    other.m_RendererID = 0;
}

MCEngine::VertexArray &MCEngine::VertexArray::operator=(VertexArray &&other)
{
    if (this != &other)
    {
        glDeleteVertexArrays(1, &m_RendererID);

        m_RendererID = other.m_RendererID;
        m_IndexBuffer = std::move(other.m_IndexBuffer);
        m_VertexBuffers = std::move(other.m_VertexBuffers);
        m_VertexAttributes = std::move(other.m_VertexAttributes);

        other.m_RendererID = 0;
    }
    return *this;
}

void MCEngine::VertexArray::Bind() const
{
    glBindVertexArray(m_RendererID);

    m_IndexBuffer.Bind();
    for (const auto &vertexBuffer : m_VertexBuffers)
    {
        vertexBuffer.Bind();
    }
}

void MCEngine::VertexArray::Render() const
{
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void MCEngine::VertexArray::Unbind() const
{
    glBindVertexArray(0);

    m_IndexBuffer.Unbind();
    for (const auto &vertexBuffer : m_VertexBuffers)
    {
        vertexBuffer.Unbind();
    }
}

void MCEngine::VertexArray::SetIndexBuffer(IndexBuffer &&indexBuffer)
{
    Bind();
    m_IndexBuffer = std::move(indexBuffer);
    m_IndexBuffer.Bind();

    GLint error = glGetError();
    if (error != GL_NO_ERROR)
    {
        std::cerr << "OpenGL Error: " << error << " in SetIndexBuffer" << std::endl;
    }

    Unbind();
}

void MCEngine::VertexArray::AddVertexBuffer(VertexBuffer &&vertexBuffer, const VertexAttribute &attribute)
{
    m_VertexBuffers.push_back(std::move(vertexBuffer));

    Bind();
    m_VertexBuffers.back().Bind();

    GLint error = glGetError();
    if (error != GL_NO_ERROR)
    {
        std::cerr << "OpenGL Error: " << error << " in AddVertexBuffer" << std::endl;
    }

    glVertexAttribPointer(attribute.location, attribute.count, attribute.type, attribute.normalized,
                          static_cast<GLsizei>(attribute.stride), attribute.offset);
    glEnableVertexAttribArray(attribute.location);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    m_VertexAttributes.push_back(attribute);

    error = glGetError();
    if (error != GL_NO_ERROR)
    {
        std::cerr << "OpenGL Error: " << error << " in AddVertexAttribute" << std::endl;
    }

    m_VertexBuffers.back().Unbind();
    Unbind();
}