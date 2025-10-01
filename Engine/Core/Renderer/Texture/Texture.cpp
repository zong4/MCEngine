#include "Texture.hpp"

#include <glad/glad.h>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

unsigned char *MCEngine::Texture::LoadImage(const std::string &path, int &width, int &height, int &channels,
                                            bool flipVertically)
{
    ENGINE_PROFILE_FUNCTION();

    // Check if file exists
    if (!std::filesystem::exists(path))
    {
        LOG_ENGINE_WARN("Texture file does not exist: " + path);
        return nullptr;
    }

    // Load image
    stbi_set_flip_vertically_on_load(flipVertically);
    unsigned char *data = stbi_load(path.c_str(), &width, &height, &channels, 0);

    if (!data)
    {
        LOG_ENGINE_ERROR("Failed to load texture: " + path);
        return nullptr;
    }
    return data;
}

void MCEngine::Texture::FreeImage(unsigned char *data)
{
    ENGINE_PROFILE_FUNCTION();

    stbi_image_free(data);
}
