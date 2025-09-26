#include "ShaderLibrary.hpp"

MCEngine::ShaderLibrary &MCEngine::ShaderLibrary::GetInstance()
{
    static ShaderLibrary instance;
    return instance;
}

std::shared_ptr<MCEngine::Shader> MCEngine::ShaderLibrary::GetShader(const std::string &name)
{
    if (!Exists(name))
    {
        LOG_ENGINE_ERROR("Shader not found: " + name);
        return nullptr;
    }

    return m_Shaders[name];
}

void MCEngine::ShaderLibrary::AddShader(const std::string &name, const std::shared_ptr<Shader> &shader)
{
    if (Exists(name))
    {
        LOG_ENGINE_ERROR("Shader already exists: " + name);
        return;
    }

    m_Shaders[name] = shader;

    LOG_ENGINE_INFO("Shader added: " + name);
}

std::shared_ptr<MCEngine::Shader> MCEngine::ShaderLibrary::LoadShader(const std::string &name,
                                                                      const std::string &vertexSource,
                                                                      const std::string &fragmentSource)
{
    auto shader = std::make_shared<MCEngine::Shader>(vertexSource, fragmentSource);
    AddShader(name, shader);
    return shader;
}

MCEngine::ShaderLibrary::ShaderLibrary()
{
    std::filesystem::path path(std::string(PROJECT_ROOT) + "/Engine/Assets/Shaders/");
    for (const auto &entry : std::filesystem::directory_iterator(path))
    {
        if (entry.path().extension() == ".vert")
        {
            std::string vertexPath = entry.path().string();

            auto fragPath = entry.path();
            std::string fragmentPath = fragPath.replace_extension(".frag").string();

            if (std::filesystem::exists(fragmentPath))
            {
                std::ifstream vertexFile(vertexPath);
                std::ifstream fragmentFile(fragmentPath);

                std::string vertexSource((std::istreambuf_iterator<char>(vertexFile)),
                                         std::istreambuf_iterator<char>());
                std::string fragmentSource((std::istreambuf_iterator<char>(fragmentFile)),
                                           std::istreambuf_iterator<char>());

                std::string shaderName = entry.path().stem().string();
                LoadShader(shaderName, vertexSource, fragmentSource);
            }
            else
            {
                LOG_ENGINE_ERROR("Fragment shader not found for: " + vertexPath);
            }
        }
    }

    LOG_ENGINE_INFO("ShaderLibrary initialized.");
}

bool MCEngine::ShaderLibrary::Exists(const std::string &name) const { return m_Shaders.find(name) != m_Shaders.end(); }