#pragma once

#include "Renderer/RendererPipeline.hpp"
#include "Renderer/ShaderLibrary.hpp"

namespace MCEngine
{

class Application
{
public:
    Application();
    virtual ~Application() = default;

    void Run();

    void AddObject(const std::shared_ptr<Object> &object);

private:
    std::unique_ptr<Window> m_Window = nullptr;
    std::vector<std::shared_ptr<Object>> m_Objects;
    std::unique_ptr<ShaderLibrary> m_ShaderLibrary = nullptr;
    std::map<std::string, std::vector<std::shared_ptr<Object>>> m_RendererPipelines;

private:
    void Init();
};

extern std::unique_ptr<Application> CreateApplication();

} // namespace MCEngine