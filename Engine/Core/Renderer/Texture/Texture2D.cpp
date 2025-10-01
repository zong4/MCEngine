#include "Texture2D.hpp"

#include <glad/glad.h>

MCEngine::Texture2D::Texture2D(int width, int height, void *data) : Texture(), m_Format(GL_RGBA), m_Samples(0)
{
    ENGINE_PROFILE_FUNCTION();

    glGenTextures(1, &m_RendererID);
    glBindTexture(GL_TEXTURE_2D, m_RendererID);

    glTexImage2D(GL_TEXTURE_2D, 0, m_Format, width, height, 0, m_Format, GL_UNSIGNED_BYTE, data);
    RendererCommand::GetError(std::string(FUNCTION_SIGNATURE));

    // Set texture parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    RendererCommand::GetError(std::string(FUNCTION_SIGNATURE));

    glBindTexture(GL_TEXTURE_2D, 0);
}

MCEngine::Texture2D::Texture2D(int width, int height, int samples) : Texture(), m_Format(GL_RGBA), m_Samples(samples)
{
    ENGINE_PROFILE_FUNCTION();

    glGenTextures(1, &m_RendererID);
    glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, m_RendererID);

    glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, samples, m_Format, width, height, GL_TRUE);
    RendererCommand::GetError(std::string(FUNCTION_SIGNATURE));

    glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, 0);
}

MCEngine::Texture2D::Texture2D(int width, int height) : Texture(), m_Format(GL_DEPTH_COMPONENT), m_Samples(0)
{
    ENGINE_PROFILE_FUNCTION();

    glGenTextures(1, &m_RendererID);
    glBindTexture(GL_TEXTURE_2D, m_RendererID);

    glTexImage2D(GL_TEXTURE_2D, 0, m_Format, width, height, 0, m_Format, GL_FLOAT, nullptr);
    RendererCommand::GetError(std::string(FUNCTION_SIGNATURE));

    // Set texture parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
    float borderColor[] = {1.0f, 1.0f, 1.0f, 1.0f};
    glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
    RendererCommand::GetError(std::string(FUNCTION_SIGNATURE));

    glBindTexture(GL_TEXTURE_2D, 0);
}

MCEngine::Texture2D::Texture2D(const std::string &path) : Texture(), m_Samples(0)
{
    ENGINE_PROFILE_FUNCTION();

    glGenTextures(1, &m_RendererID);
    glBindTexture(GL_TEXTURE_2D, m_RendererID);

    // Load image
    {
        int width, height, channels;
        unsigned char *data = LoadImage(path, width, height, channels, true);

        m_Format = (channels == 4) ? GL_RGBA : GL_RGB;
        glTexImage2D(GL_TEXTURE_2D, 0, m_Format, width, height, 0, m_Format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
        RendererCommand::GetError(std::string(FUNCTION_SIGNATURE));

        FreeImage(data);
    }

    // Set texture parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    RendererCommand::GetError(std::string(FUNCTION_SIGNATURE));

    glBindTexture(GL_TEXTURE_2D, 0);
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
    RendererCommand::GetError(std::string(FUNCTION_SIGNATURE));
}

void MCEngine::Texture2D::Unbind() const
{
    ENGINE_PROFILE_FUNCTION();

    glBindTexture(GL_TEXTURE_2D, 0);
    RendererCommand::GetError(std::string(FUNCTION_SIGNATURE));
}

void MCEngine::Texture2D::Resize(int width, int height)
{
    ENGINE_PROFILE_FUNCTION();

    if (m_Samples == 0)
    {
        glBindTexture(GL_TEXTURE_2D, m_RendererID);
        m_Format == GL_DEPTH_COMPONENT
            ? glTexImage2D(GL_TEXTURE_2D, 0, m_Format, width, height, 0, m_Format, GL_FLOAT, nullptr)
            : glTexImage2D(GL_TEXTURE_2D, 0, m_Format, width, height, 0, m_Format, GL_UNSIGNED_BYTE, nullptr);
        glBindTexture(GL_TEXTURE_2D, 0);
    }
    else
    {
        glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, m_RendererID);
        glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, m_Samples, m_Format, width, height, GL_TRUE);
        glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, 0);
    }
    RendererCommand::GetError(std::string(FUNCTION_SIGNATURE));
}
