#include "ShaderLibrary.hpp"

bool MCEngine::ShaderLibrary::Exists(const std::string &name) const { return m_Shaders.find(name) != m_Shaders.end(); }

std::shared_ptr<MCEngine::Shader> MCEngine::ShaderLibrary::Get(const std::string &name)
{
    if (!Exists(name))
    {
        LOG_ENGINE_ERROR("Shader not found: " + name);
        return nullptr;
    }
    return m_Shaders[name];
}

void MCEngine::ShaderLibrary::Add(const std::string &name, const std::shared_ptr<Shader> &shader)
{
    if (Exists(name))
    {
        LOG_ENGINE_ERROR("Shader already exists: " + name);
        return;
    }
    m_Shaders[name] = shader;
}

std::shared_ptr<MCEngine::Shader> MCEngine::ShaderLibrary::Load(const std::string &name,
                                                                const std::string &vertexSource,
                                                                const std::string &fragmentSource)
{
    auto shader = std::make_shared<MCEngine::Shader>(vertexSource, fragmentSource);
    Add(name, shader);
    return shader;
}