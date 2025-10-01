#pragma once

#include "Texture.hpp"

namespace MCEngine
{

class TextureCube : public Texture
{
public:
    TextureCube(const std::string &directory);
    virtual ~TextureCube() override;

public:
    virtual void Bind(unsigned int slot) const override;
    virtual void Unbind() const override;

private:
    void LoadCubemap(const std::array<std::string, 6> &faces);
};

} // namespace MCEngine