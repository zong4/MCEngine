#pragma once

#include "ECS/Component/Component.hpp"

namespace MCEngine
{

class SkyboxComponent : public Component
{
public:
    SkyboxComponent(const std::string &name);
    ~SkyboxComponent();

    // Getters
    std::shared_ptr<TextureCube> &GetTextureCubePtr() { return m_TextureCubePtr; }
    const std::shared_ptr<TextureCube> &GetTextureCubePtr() const { return m_TextureCubePtr; }

    // Setters
    void SetTextureCube(const std::shared_ptr<TextureCube> &textureCube) { m_TextureCubePtr = textureCube; }

public:
    virtual void Update(float deltaTime) override {}

private:
    std::shared_ptr<TextureCube> m_TextureCubePtr;
};

} // namespace MCEngine