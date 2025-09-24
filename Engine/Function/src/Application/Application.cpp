#include "Application.hpp"

#include "Object/Square.hpp"
#include "Renderer/ShaderLibrary.hpp"

MCEngine::Application::Application() { Init(); }

void MCEngine::Application::Run()
{
    while (!m_Window->ShouldClose())
    {
        m_Window->PreUpdate();

        for (auto &pipelinePair : m_RendererPipelines)
        {
            ShaderLibrary::GetInstance().Get(pipelinePair.first)->Bind();
            ShaderLibrary::GetInstance().Get(pipelinePair.first)->SetUniformMat4("u_View", m_Camera->GetView());
            ShaderLibrary::GetInstance()
                .Get(pipelinePair.first)
                ->SetUniformMat4("u_Projection", m_Camera->GetProjection());
            for (const auto &object : pipelinePair.second)
            {
                object->Render(pipelinePair.first);
            }
            ShaderLibrary::GetInstance().Get(pipelinePair.first)->Unbind();
        }

        m_Window->Update();
        for (auto &object : m_Objects)
        {
            object->Update();
        }

        m_Window->PostUpdate();
    }
}

void MCEngine::Application::Init()
{
    MCEngine::Logger::Init();

    m_Window = std::make_unique<Window>(800, 600, "Minecraft Engine");

    m_Camera = std::make_unique<OrthoCamera>(glm::vec2(0.5f, 0.0f), glm::vec2(8.0f, 6.0f));

    AddObject(Square::GetIdentitySquare(), "Standard");
}

void MCEngine::Application::AddObject(const std::shared_ptr<Object> &object, const std::string &pipeline)
{
    m_Objects.push_back(object);
    m_RendererPipelines[pipeline].push_back(object);
}