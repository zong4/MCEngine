#include "Texture.hpp"

#include <glad/glad.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#define GL_ERROR()                                                                                                     \
    {                                                                                                                  \
        GLint error = glGetError();                                                                                    \
        if (error != GL_NO_ERROR)                                                                                      \
        {                                                                                                              \
            LOG_ENGINE_ERROR("OpenGL Error: " + std::to_string(error) + " in " + std::string(__FUNCTION__));           \
        }                                                                                                              \
    }

MCEngine::Texture::Texture(int width, int height, void *data) : m_Format(GL_RGBA)
{
    ENGINE_PROFILE_FUNCTION();

    glGenTextures(1, &m_RendererID);
    glBindTexture(GL_TEXTURE_2D, m_RendererID);
    glTexImage2D(GL_TEXTURE_2D, 0, m_Format, width, height, 0, m_Format, GL_UNSIGNED_BYTE, data);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    GL_ERROR();
}

MCEngine::Texture::Texture(const std::string &path)
{
    ENGINE_PROFILE_FUNCTION();

    glGenTextures(1, &m_RendererID);
    glBindTexture(GL_TEXTURE_2D, m_RendererID);

    // Set texture parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    GL_ERROR();

    // Load image
    int width, height, channels;
    stbi_set_flip_vertically_on_load(1);
    unsigned char *imageData = stbi_load(path.c_str(), &width, &height, &channels, 0);
    if (imageData)
    {
        m_Format = (channels == 4) ? GL_RGBA : GL_RGB;
        glTexImage2D(GL_TEXTURE_2D, 0, m_Format, width, height, 0, m_Format, GL_UNSIGNED_BYTE, imageData);
        glGenerateMipmap(GL_TEXTURE_2D);
        GL_ERROR();

        stbi_image_free(imageData);
    }
    else
    {
        LOG_ENGINE_ERROR("Failed to load texture: " + path);
    }
}

MCEngine::Texture::~Texture()
{
    ENGINE_PROFILE_FUNCTION();

    glDeleteTextures(1, &m_RendererID);
}

void MCEngine::Texture::Bind(unsigned int slot) const
{
    ENGINE_PROFILE_FUNCTION();

    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(GL_TEXTURE_2D, m_RendererID);
    GL_ERROR();
}

void MCEngine::Texture::Unbind() const
{
    ENGINE_PROFILE_FUNCTION();

    glBindTexture(GL_TEXTURE_2D, 0);
    GL_ERROR();
}

void MCEngine::Texture::Resize(int width, int height)
{
    ENGINE_PROFILE_FUNCTION();

    glBindTexture(GL_TEXTURE_2D, m_RendererID);
    glTexImage2D(GL_TEXTURE_2D, 0, m_Format, width, height, 0, m_Format, GL_UNSIGNED_BYTE, nullptr);
    GL_ERROR();
}