#pragma once

#include "pch.hpp"

namespace MCEngine
{

class ShaderLibrary
{
public:
    ShaderLibrary() = default;
    ~ShaderLibrary() = default;
    ShaderLibrary(const ShaderLibrary &) = delete;
    ShaderLibrary &operator=(const ShaderLibrary &) = delete;

    bool Exists(const std::string &name) const;

    std::shared_ptr<Shader> Get(const std::string &name);

    void Add(const std::string &name, const std::shared_ptr<Shader> &shader);
    std::shared_ptr<Shader> Load(const std::string &name, const std::string &vertexSource,
                                 const std::string &fragmentSource);

private:
    std::unordered_map<std::string, std::shared_ptr<Shader>> m_Shaders;
};

} // namespace MCEngine