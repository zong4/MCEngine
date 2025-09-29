#include "UniformBuffer.hpp"

#include <glad/glad.h>

#define GL_ERROR()                                                                                                     \
    {                                                                                                                  \
        GLint error = glGetError();                                                                                    \
        if (error != GL_NO_ERROR)                                                                                      \
        {                                                                                                              \
            LOG_ENGINE_ERROR("OpenGL Error: " + std::to_string(error) + " in " + std::string(__FUNCTION__));           \
        }                                                                                                              \
    }

MCEngine::UniformBuffer::UniformBuffer(size_t size, unsigned int binding) : m_Binding(binding)
{
    ENGINE_PROFILE_FUNCTION();

    glGenBuffers(1, &m_RendererID);
    glBindBuffer(GL_UNIFORM_BUFFER, m_RendererID);
    glBufferData(GL_UNIFORM_BUFFER, size, nullptr, GL_DYNAMIC_DRAW);
    glBindBufferBase(GL_UNIFORM_BUFFER, m_Binding, m_RendererID);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);

    LOG_ENGINE_INFO("UniformBuffer created with ID: " + std::to_string(m_RendererID) +
                    ", Size: " + std::to_string(size) + ", Binding: " + std::to_string(m_Binding));
}

MCEngine::UniformBuffer::~UniformBuffer() { glDeleteBuffers(1, &m_RendererID); }

void MCEngine::UniformBuffer::Bind() const { glBindBuffer(GL_UNIFORM_BUFFER, m_RendererID); }

void MCEngine::UniformBuffer::Unbind() const { glBindBuffer(GL_UNIFORM_BUFFER, 0); }

void MCEngine::UniformBuffer::SetData(const void *data, size_t size, size_t offset)
{
    ENGINE_PROFILE_FUNCTION();

    glBindBuffer(GL_UNIFORM_BUFFER, m_RendererID);
    glBufferSubData(GL_UNIFORM_BUFFER, offset, size, data);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
    GL_ERROR();
}
