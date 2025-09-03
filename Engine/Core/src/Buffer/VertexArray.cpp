#include "VertexArray.hpp"

#include <glad/glad.h>

VertexArray::VertexArray()
{
    glGenVertexArrays(1, &m_RendererID);
}

VertexArray::~VertexArray()
{
    glDeleteVertexArrays(1, &m_RendererID);
}

void VertexArray::Bind() const
{
    glBindVertexArray(m_RendererID);
}

void VertexArray::Unbind() const
{
    glBindVertexArray(0);
}

void VertexArray::SetIndexBuffer(const IndexBuffer &indexBuffer)
{
    Bind();
    indexBuffer.Bind();

    m_IndexBuffer = indexBuffer;

    GLint error = glGetError();
    if (error != GL_NO_ERROR)
    {
        std::cerr << "OpenGL Error: " << error << " in SetIndexBuffer" << std::endl;
    }

    // m_IndexBuffer.Unbind();
    Unbind();
}

void VertexArray::AddVertexBuffer(VertexBuffer &&vertexBuffer)
{
    m_VertexBuffers.push_back(std::move(vertexBuffer));

    Bind();
    m_VertexBuffers.back().Bind();

    GLint error = glGetError();
    if (error != GL_NO_ERROR)
    {
        std::cerr << "OpenGL Error: " << error << " in AddVertexBuffer" << std::endl;
    }

    m_VertexBuffers.back().Unbind();
    Unbind();
}

void VertexArray::AddVertexAttribute(const VertexAttribute &attribute)
{
    Bind();

    m_VertexBuffers.back().Bind();
    glVertexAttribPointer(attribute.location, attribute.count, attribute.type, attribute.normalized,
                          static_cast<GLsizei>(attribute.stride), attribute.offset);
    glEnableVertexAttribArray(attribute.location);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    m_VertexAttributes.push_back(attribute);

    GLint error = glGetError();
    if (error != GL_NO_ERROR)
    {
        std::cerr << "OpenGL Error: " << error << " in AddVertexAttribute" << std::endl;
    }

    m_VertexBuffers.back().Unbind();
    Unbind();
}