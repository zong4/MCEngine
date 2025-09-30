#include "VertexArray.hpp"

#include <glad/glad.h>

#define GL_ERROR()                                                                                                     \
    {                                                                                                                  \
        GLint error = glGetError();                                                                                    \
        if (error != GL_NO_ERROR)                                                                                      \
        {                                                                                                              \
            LOG_ENGINE_ERROR("OpenGL Error: " + std::to_string(error) + " in " + std::string(__FUNCTION__));           \
        }                                                                                                              \
    }

MCEngine::VertexArray::VertexArray(VertexBuffer &&vertexBuffer, const std::vector<VertexAttribute> &attributes,
                                   IndexBuffer &&indexBuffer, int count)
    : m_VertexBuffer(std::move(vertexBuffer)), m_IndexBuffer(std::move(indexBuffer)), m_Count(count)
{
    ENGINE_PROFILE_FUNCTION();

    glGenVertexArrays(1, &m_RendererID);
    SetVertexAttributes(attributes);
    LOG_ENGINE_INFO("VertexArray created with ID: " + std::to_string(m_RendererID) +
                    ", VertexBuffer ID: " + std::to_string(m_VertexBuffer.GetRendererID()) +
                    ", IndexBuffer ID: " + std::to_string(m_IndexBuffer.GetRendererID()));
}

MCEngine::VertexArray::~VertexArray() { glDeleteVertexArrays(1, &m_RendererID); }

MCEngine::VertexArray::VertexArray(VertexArray &&other)
    : m_RendererID(other.m_RendererID), m_IndexBuffer(std::move(other.m_IndexBuffer)),
      m_VertexBuffer(std::move(other.m_VertexBuffer)), m_Count(other.m_Count)
{
    LOG_ENGINE_INFO("VertexArray moved with ID: " + std::to_string(m_RendererID));

    // Invalidate the moved-from object
    other.m_RendererID = 0;
    other.m_Count = 1;
}

MCEngine::VertexArray &MCEngine::VertexArray::operator=(VertexArray &&other)
{
    if (this != &other)
    {
        glDeleteVertexArrays(1, &m_RendererID);

        m_RendererID = other.m_RendererID;
        m_IndexBuffer = std::move(other.m_IndexBuffer);
        m_VertexBuffer = std::move(other.m_VertexBuffer);
        m_Count = other.m_Count;
        LOG_ENGINE_INFO("VertexArray move-assigned with ID: " + std::to_string(m_RendererID));

        // Invalidate the moved-from object
        other.m_RendererID = 0;
        other.m_Count = 1;
    }
    return *this;
}

void MCEngine::VertexArray::SetVertexBuffer(VertexBuffer &&vertexBuffer, const std::vector<VertexAttribute> &attributes)
{
    ENGINE_PROFILE_FUNCTION();

    m_VertexBuffer = std::move(vertexBuffer);
    SetVertexAttributes(attributes);
    LOG_ENGINE_INFO("VertexArray ID: " + std::to_string(m_RendererID) +
                    " set with new VertexBuffer ID: " + std::to_string(m_VertexBuffer.GetRendererID()));
}

void MCEngine::VertexArray::SetIndexBuffer(IndexBuffer &&indexBuffer)
{
    ENGINE_PROFILE_FUNCTION();

    m_IndexBuffer = std::move(indexBuffer);
    LOG_ENGINE_INFO("VertexArray ID: " + std::to_string(m_RendererID) +
                    " set with new IndexBuffer ID: " + std::to_string(m_IndexBuffer.GetRendererID()));
}

void MCEngine::VertexArray::Render(RendererType renderType) const
{
    ENGINE_PROFILE_FUNCTION();

    Bind();
    m_VertexBuffer.Bind();

    if (m_IndexBuffer.GetRendererID() == 0)
    {
        m_Count == 1 ? glDrawArrays(static_cast<GLenum>(renderType), 0, m_VertexBuffer.GetCount() / m_AttributeCount)
                     : glDrawArraysInstanced(static_cast<GLenum>(renderType), 0,
                                             m_VertexBuffer.GetCount() / m_AttributeCount, m_Count);
        GL_ERROR();
    }
    else
    {
        m_IndexBuffer.Bind();
        m_Count == 1 ? glDrawElements(static_cast<GLenum>(renderType), m_IndexBuffer.GetCount(), GL_UNSIGNED_INT, 0)
                     : glDrawElementsInstanced(static_cast<GLenum>(renderType), m_IndexBuffer.GetCount(),
                                               GL_UNSIGNED_INT, 0, m_Count);
        GL_ERROR();
        m_IndexBuffer.Unbind();
    }

    m_VertexBuffer.Unbind();
    Unbind();
}

void MCEngine::VertexArray::Bind() const { glBindVertexArray(m_RendererID); }

void MCEngine::VertexArray::Unbind() const { glBindVertexArray(0); }

void MCEngine::VertexArray::SetVertexAttributes(const std::vector<VertexAttribute> &attributes)
{
    ENGINE_PROFILE_FUNCTION();

    Bind();
    for (const auto &attribute : attributes)
    {
        glVertexAttribPointer(attribute.location, attribute.count, attribute.type, attribute.normalized,
                              static_cast<GLsizei>(attribute.stride), attribute.offset);
        glEnableVertexAttribArray(attribute.location);
        GL_ERROR();
    }
    m_AttributeCount = static_cast<int>(attributes.size());
    Unbind();

    LOG_ENGINE_INFO("VertexArray ID: " + std::to_string(m_RendererID) + " vertex attributes(" +
                    std::to_string(m_AttributeCount) + ") set/updated");
}