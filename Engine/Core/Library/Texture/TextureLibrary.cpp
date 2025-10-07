#include "TextureLibrary.hpp"

#include <glad/glad.h>

MCEngine::TextureLibrary &MCEngine::TextureLibrary::GetInstance()
{
    static TextureLibrary instance;
    return instance;
}

std::string MCEngine::TextureLibrary::GetName(const std::shared_ptr<Texture> &texture) const
{
    for (const auto &[name, ptr] : m_Textures)
    {
        if (ptr == texture)
            return name;
    }
    LOG_ENGINE_WARN("Texture not found in library");
    return "";
}

std::shared_ptr<MCEngine::Texture2D> MCEngine::TextureLibrary::GetTexture2D(const std::string &name)
{
    ENGINE_PROFILE_FUNCTION();

    if (!Exists(name))
    {
        LOG_ENGINE_ERROR("Texture not found: " + name);
        return nullptr;
    }
    return std::dynamic_pointer_cast<Texture2D>(m_Textures[name]);
}

std::shared_ptr<MCEngine::TextureCube> MCEngine::TextureLibrary::GetTextureCube(const std::string &name)
{
    ENGINE_PROFILE_FUNCTION();

    if (!Exists(name))
    {
        LOG_ENGINE_ERROR("Texture not found: " + name);
        return nullptr;
    }
    return std::dynamic_pointer_cast<TextureCube>(m_Textures[name]);
}

void MCEngine::TextureLibrary::AddTexture(const std::string &name, const std::shared_ptr<Texture> &texture)
{
    ENGINE_PROFILE_FUNCTION();

    if (Exists(name))
    {
        LOG_ENGINE_ERROR("Texture already exists: " + name);
        return;
    }
    m_Textures[name] = texture;
    LOG_ENGINE_TRACE("Texture added: " + name);
}

MCEngine::TextureLibrary::TextureLibrary()
{
    ENGINE_PROFILE_FUNCTION();

    AddTexture("White", std::make_shared<Texture2D>(1, 1, GL_RGBA8, GL_RGBA, GL_UNSIGNED_BYTE,
                                                    new unsigned char[4]{255, 255, 255, 255}));

    std::filesystem::path path(std::string(PROJECT_ROOT) + "/Engine/Resources/Images/");
    if (!std::filesystem::exists(path))
    {
        LOG_ENGINE_ERROR("Texture directory does not exist: " + path.string());
        return;
    }

    for (auto &&entry : std::filesystem::directory_iterator(path))
    {
        if (entry.is_regular_file())
        {
            if (entry.path().extension() == ".png" || entry.path().extension() == ".jpg")
            {
                AddTexture(entry.path().stem().string(), std::make_shared<Texture2D>(entry.path().string()));
            }
        }
        else if (entry.is_directory())
        {
            AddTexture(entry.path().stem().string(), std::make_shared<TextureCube>(entry.path().string()));
        }
    }

    LOG_ENGINE_INFO("Texture Library initialized");
}

bool MCEngine::TextureLibrary::Exists(const std::string &name) const
{
    return m_Textures.find(name) != m_Textures.end();
}
