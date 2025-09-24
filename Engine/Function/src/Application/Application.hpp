#pragma once

#include "Object/Object.hpp"

namespace MCEngine
{

class Application
{
public:
    Application();
    virtual ~Application() = default;

    void Run();

    void AddObject(const std::shared_ptr<Object> &object, const std::string &pipeline);

private:
    std::unique_ptr<Window> m_Window = nullptr;
    std::vector<std::shared_ptr<Object>> m_Objects;
    std::map<std::string, std::vector<std::shared_ptr<Object>>> m_RendererPipelines;

private:
    void Init();
};

extern std::unique_ptr<Application> CreateApplication();

} // namespace MCEngine