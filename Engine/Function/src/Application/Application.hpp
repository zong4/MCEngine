#pragma once

#include "Object/Camera/OrthoCamera.hpp"
#include "Object/Object.hpp"
#include "pch.hpp"

namespace MCEngine
{

class Application
{
public:
    Application();
    virtual ~Application() = default;

    void AddLayer(const std::shared_ptr<Layer> &layer) { m_Window->AddLayer(layer); }
    void RemoveLayer(const std::shared_ptr<Layer> &layer) { m_Window->RemoveLayer(layer); }

    void AddObject(const std::shared_ptr<Object> &object, const std::string &pipeline);

public:
    void Run();

private:
    std::unique_ptr<Window> m_Window = nullptr;
    std::unique_ptr<OrthoCamera> m_Camera = nullptr;

    std::vector<std::shared_ptr<Object>> m_Objects;
    std::map<std::string, std::vector<std::shared_ptr<Object>>> m_RendererPipelines;

private:
    void Init();
};

extern std::unique_ptr<Application> CreateApplication();

} // namespace MCEngine