#pragma once

#include "pch.hpp"

namespace MCEngine
{

class ShaderLibrary
{
public:
    static ShaderLibrary &GetInstance();

    std::shared_ptr<Shader> Get(const std::string &name);

    void Add(const std::string &name, const std::shared_ptr<Shader> &shader);
    std::shared_ptr<Shader> Load(const std::string &name, const std::string &vertexSource,
                                 const std::string &fragmentSource);

private:
    std::unordered_map<std::string, std::shared_ptr<Shader>> m_Shaders;

private:
    ShaderLibrary();
    ~ShaderLibrary() = default;

    bool Exists(const std::string &name) const;
};

} // namespace MCEngine