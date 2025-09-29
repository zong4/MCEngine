#include "TextureLibrary.hpp"

MCEngine::TextureLibrary &MCEngine::TextureLibrary::GetInstance()
{
    static TextureLibrary instance;
    return instance;
}

std::shared_ptr<MCEngine::Texture> MCEngine::TextureLibrary::GetTexture(const std::string &name)
{
    ENGINE_PROFILE_FUNCTION();

    if (!Exists(name))
    {
        LOG_ENGINE_ERROR("Texture not found: " + name);
        return nullptr;
    }
    return m_TextureMap[name];
}

void MCEngine::TextureLibrary::AddTexture(const std::string &name, const std::shared_ptr<Texture> &texturePtr)
{
    ENGINE_PROFILE_FUNCTION();

    if (Exists(name))
    {
        LOG_ENGINE_ERROR("Texture already exists: " + name);
        return;
    }
    m_TextureMap[name] = texturePtr;

    LOG_ENGINE_INFO("Texture added: " + name);
}

bool MCEngine::TextureLibrary::Exists(const std::string &name) const
{
    return m_TextureMap.find(name) != m_TextureMap.end();
}

MCEngine::TextureLibrary::TextureLibrary()
{
    ENGINE_PROFILE_FUNCTION();

    AddTexture("White", std::make_shared<Texture>(1, 1, new unsigned char[4]{255, 255, 255, 255}));

    std::filesystem::path path(std::string(PROJECT_ROOT) + "/Engine/Assets/Images/");
    for (const auto &entry : std::filesystem::directory_iterator(path))
    {
        if (entry.path().extension() == ".png" || entry.path().extension() == ".jpg")
        {
            std::string texturePath = entry.path().string();
            AddTexture(entry.path().stem().string(), std::make_shared<Texture>(texturePath));
        }
    }

    LOG_ENGINE_INFO("TextureLibrary initialized.");
}