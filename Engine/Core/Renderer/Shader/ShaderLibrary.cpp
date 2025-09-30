#include "ShaderLibrary.hpp"

MCEngine::ShaderLibrary &MCEngine::ShaderLibrary::GetInstance()
{
    static ShaderLibrary instance;
    return instance;
}

std::shared_ptr<MCEngine::Shader> MCEngine::ShaderLibrary::GetShader(const std::string &name)
{
    ENGINE_PROFILE_FUNCTION();

    if (!Exists(name))
    {
        LOG_ENGINE_ERROR("Shader not found: " + name);
        return nullptr;
    }
    return m_ShaderMap[name];
}

void MCEngine::ShaderLibrary::AddShader(const std::string &name, const std::shared_ptr<Shader> &shader)
{
    ENGINE_PROFILE_FUNCTION();

    if (Exists(name))
    {
        LOG_ENGINE_ERROR("Shader already exists: " + name);
        return;
    }
    m_ShaderMap[name] = shader;

    LOG_ENGINE_INFO("Shader added: " + name);
}

std::shared_ptr<MCEngine::Shader> MCEngine::ShaderLibrary::LoadShader(const std::string &name,
                                                                      const std::string &vertexSource,
                                                                      const std::string &fragmentSource,
                                                                      const std::string &geometrySource)
{
    ENGINE_PROFILE_FUNCTION();

    if (Exists(name))
    {
        LOG_ENGINE_ERROR("Shader already exists: " + name);
        return m_ShaderMap[name];
    }

    auto shader = std::make_shared<MCEngine::Shader>(vertexSource, fragmentSource, geometrySource);
    AddShader(name, shader);
    return shader;
}

MCEngine::ShaderLibrary::ShaderLibrary()
{
    ENGINE_PROFILE_FUNCTION();

    std::filesystem::path path(std::string(PROJECT_ROOT) + "/Engine/Assets/Shaders/");
    for (const auto &entry : std::filesystem::recursive_directory_iterator(path))
    {
        if (entry.path().extension() == ".vs")
        {
            std::string vertexPath = entry.path().string();
            auto fragPath = entry.path();
            std::string fragmentPath = fragPath.replace_extension(".fs").string();
            if (std::filesystem::exists(fragmentPath))
            {
                std::string shaderName = entry.path().stem().string();

                std::ifstream vertexFile(vertexPath);
                std::string vertexSource((std::istreambuf_iterator<char>(vertexFile)),
                                         std::istreambuf_iterator<char>());

                std::ifstream fragmentFile(fragmentPath);
                std::string fragmentSource((std::istreambuf_iterator<char>(fragmentFile)),
                                           std::istreambuf_iterator<char>());

                auto geomPath = entry.path();
                std::string geometryPath = geomPath.replace_extension(".gs").string();
                if (std::filesystem::exists(geometryPath))
                {
                    std::ifstream geometryFile(geometryPath);
                    std::string geometrySource((std::istreambuf_iterator<char>(geometryFile)),
                                               std::istreambuf_iterator<char>());
                    LoadShader(shaderName, vertexSource, fragmentSource, geometrySource);
                }
                else
                {
                    LoadShader(shaderName, vertexSource, fragmentSource);
                }
            }
            else
            {
                LOG_ENGINE_ERROR("Fragment shader not found for: " + vertexPath);
            }
        }
    }

    LOG_ENGINE_INFO("ShaderLibrary initialized");
}

bool MCEngine::ShaderLibrary::Exists(const std::string &name) const
{
    return m_ShaderMap.find(name) != m_ShaderMap.end();
}