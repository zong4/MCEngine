#include "SkyboxComponent.hpp"

MCEngine::SkyboxComponent::SkyboxComponent(const std::string &name)
{
    m_TextureCubePtr = TextureLibrary::GetInstance().GetTextureCube(name);
    LOG_ENGINE_INFO("Skybox Component created with name: " + name);
}

MCEngine::SkyboxComponent::~SkyboxComponent() {}