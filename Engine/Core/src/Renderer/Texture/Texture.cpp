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

MCEngine::Texture2D::Texture2D(int width, int height, void *data) : m_Format(GL_RGBA)
{
    ENGINE_PROFILE_FUNCTION();

    glGenTextures(1, &m_RendererID);
    glBindTexture(GL_TEXTURE_2D, m_RendererID);
    glTexImage2D(GL_TEXTURE_2D, 0, m_Format, width, height, 0, m_Format, GL_UNSIGNED_BYTE, data);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    GL_ERROR();
}

MCEngine::Texture2D::Texture2D(const std::string &path)
{
    ENGINE_PROFILE_FUNCTION();

    glGenTextures(1, &m_RendererID);
    glBindTexture(GL_TEXTURE_2D, m_RendererID);

    // Set texture parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
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

MCEngine::Texture2D::~Texture2D()
{
    ENGINE_PROFILE_FUNCTION();

    glDeleteTextures(1, &m_RendererID);
}

void MCEngine::Texture2D::Bind(unsigned int slot) const
{
    ENGINE_PROFILE_FUNCTION();

    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(GL_TEXTURE_2D, m_RendererID);
    GL_ERROR();
}

void MCEngine::Texture2D::Unbind() const
{
    ENGINE_PROFILE_FUNCTION();

    glBindTexture(GL_TEXTURE_2D, 0);
    GL_ERROR();
}

void MCEngine::Texture2D::Resize(int width, int height)
{
    ENGINE_PROFILE_FUNCTION();

    glBindTexture(GL_TEXTURE_2D, m_RendererID);
    glTexImage2D(GL_TEXTURE_2D, 0, m_Format, width, height, 0, m_Format, GL_UNSIGNED_BYTE, nullptr);
    GL_ERROR();
}

MCEngine::TextureCube::TextureCube(const std::string &directory) : m_RendererID(0)
{
    std::array<std::string, 6> faces = {directory + "/right.jpg",  directory + "/left.jpg",  directory + "/top.jpg",
                                        directory + "/bottom.jpg", directory + "/front.jpg", directory + "/back.jpg"};
    LoadCubemap(faces);
}

MCEngine::TextureCube::~TextureCube() { glDeleteTextures(1, &m_RendererID); }

void MCEngine::TextureCube::Bind(unsigned int slot) const
{
    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(GL_TEXTURE_CUBE_MAP, m_RendererID);
    GL_ERROR();
}

void MCEngine::TextureCube::Unbind() const
{
    glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
    GL_ERROR();
}

void MCEngine::TextureCube::LoadCubemap(const std::array<std::string, 6> &faces)
{
    ENGINE_PROFILE_FUNCTION();

    glGenTextures(1, &m_RendererID);
    glBindTexture(GL_TEXTURE_CUBE_MAP, m_RendererID);

    // Set texture parameters
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    GL_ERROR();

    int width, height, channels;
    stbi_set_flip_vertically_on_load(false);
    for (unsigned int i = 0; i < faces.size(); i++)
    {
        unsigned char *data = stbi_load(faces[i].c_str(), &width, &height, &channels, 0);
        if (data)
        {
            GLenum format;
            if (channels == 1)
                format = GL_RED;
            else if (channels == 3)
                format = GL_RGB;
            else if (channels == 4)
                format = GL_RGBA;
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE,
                         data);
            GL_ERROR();
        }
        else
        {
            LOG_ENGINE_ERROR("Failed to load TextureCube texture at path: " + faces[i]);
        }
        stbi_image_free(data);
    }

    LOG_ENGINE_INFO("TextureCube created with RendererID: " + std::to_string((uint32_t)m_RendererID));
}