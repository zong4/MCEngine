#include "TextureCube.hpp"

#include <glad/glad.h>

MCEngine::TextureCube::TextureCube(const std::string &directory) : Texture()
{
    std::array<std::string, 6> faces = {directory + "/right.jpg",  directory + "/left.jpg",  directory + "/top.jpg",
                                        directory + "/bottom.jpg", directory + "/front.jpg", directory + "/back.jpg"};
    LoadCubemap(faces);
}

MCEngine::TextureCube::~TextureCube()
{
    ENGINE_PROFILE_FUNCTION();

    glDeleteTextures(1, &m_RendererID);
}

void MCEngine::TextureCube::Bind(unsigned int slot) const
{
    ENGINE_PROFILE_FUNCTION();

    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(GL_TEXTURE_CUBE_MAP, m_RendererID);
    RendererCommand::GetError(std::string(FUNCTION_SIGNATURE));
}

void MCEngine::TextureCube::Unbind() const
{
    ENGINE_PROFILE_FUNCTION();

    glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
    RendererCommand::GetError(std::string(FUNCTION_SIGNATURE));
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
    RendererCommand::GetError(std::string(FUNCTION_SIGNATURE));

    int width, height, channels;
    unsigned char *data = nullptr;
    for (unsigned int i = 0; i < faces.size(); i++)
    {
        data = LoadImage(faces[i], width, height, channels, false);

        GLenum format;
        if (channels == 1)
            format = GL_RED;
        else if (channels == 3)
            format = GL_RGB;
        else if (channels == 4)
            format = GL_RGBA;
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        RendererCommand::GetError(std::string(FUNCTION_SIGNATURE));

        FreeImage(data);
    }

    glBindTexture(GL_TEXTURE_CUBE_MAP, 0);

    LOG_ENGINE_INFO("TextureCube created with RendererID: " + std::to_string((uint32_t)m_RendererID));
}