#include "SkyboxComponent.hpp"

MCEngine::SkyboxComponent::SkyboxComponent(const std::shared_ptr<TextureCube> &textureCube)
    : m_TextureCubePtr(textureCube)
{
    LOG_ENGINE_INFO("Skybox Component created");
}
