#include "Texture2DLibrary.hpp"

MCEngine::Texture2DLibrary &MCEngine::Texture2DLibrary::GetInstance()
{
    static Texture2DLibrary instance;
    return instance;
}

std::shared_ptr<MCEngine::Texture2D> MCEngine::Texture2DLibrary::GetTexture(const std::string &name)
{
    ENGINE_PROFILE_FUNCTION();

    if (!Exists(name))
    {
        LOG_ENGINE_ERROR("Texture2D not found: " + name);
        return nullptr;
    }
    return m_TextureMap[name];
}

void MCEngine::Texture2DLibrary::AddTexture(const std::string &name, const std::shared_ptr<Texture2D> &texturePtr)
{
    ENGINE_PROFILE_FUNCTION();

    if (Exists(name))
    {
        LOG_ENGINE_ERROR("Texture2D already exists: " + name);
        return;
    }
    m_TextureMap[name] = texturePtr;

    LOG_ENGINE_INFO("Texture2D added: " + name);
}

bool MCEngine::Texture2DLibrary::Exists(const std::string &name) const
{
    return m_TextureMap.find(name) != m_TextureMap.end();
}

MCEngine::Texture2DLibrary::Texture2DLibrary()
{
    ENGINE_PROFILE_FUNCTION();

    AddTexture("White", std::make_shared<Texture2D>(1, 1, new unsigned char[4]{255, 255, 255, 255}));

    std::filesystem::path path(std::string(PROJECT_ROOT) + "/Engine/Assets/Images/");
    for (const auto &entry : std::filesystem::directory_iterator(path))
    {
        if (entry.path().extension() == ".png" || entry.path().extension() == ".jpg")
        {
            std::string texturePath = entry.path().string();
            AddTexture(entry.path().stem().string(), std::make_shared<Texture2D>(texturePath));
        }
    }

    LOG_ENGINE_INFO("Texture2DLibrary initialized");
}