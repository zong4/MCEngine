#include "ShaderLibrary.hpp"

void ShaderLibrary::Add(const std::string &name, const std::shared_ptr<Shader> &shader)
{
    if (Exists(name))
    {
        std::cerr << "Shader already exists: " << name << std::endl;
        return;
    }
    m_Shaders[name] = shader;
}

std::shared_ptr<Shader> ShaderLibrary::Load(const std::string &name, const std::string &vertexSource,
                                            const std::string &fragmentSource)
{
    auto shader = std::make_shared<Shader>(vertexSource, fragmentSource);
    Add(name, shader);
    return shader;
}

std::shared_ptr<Shader> ShaderLibrary::Get(const std::string &name)
{
    if (!Exists(name))
    {
        std::cerr << "Shader not found: " << name << std::endl;
        return nullptr;
    }
    return m_Shaders[name];
}

bool ShaderLibrary::Exists(const std::string &name) const
{
    return m_Shaders.find(name) != m_Shaders.end();
}