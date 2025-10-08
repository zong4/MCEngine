#include "SkyboxComponent.hpp"

MCEngine::SkyboxComponent::SkyboxComponent(const std::shared_ptr<TextureCube> &textureCube) : m_TextureCube(textureCube)
{
    LOG_ENGINE_TRACE("Skybox Component created");
}
