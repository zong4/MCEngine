#include "Application.hpp"

#include "Object/Square.hpp"

MCEngine::Application::Application() { Init(); }

void MCEngine::Application::Run()
{
    while (!m_Window->ShouldClose())
    {
        m_Window->PreUpdate();

        for (auto &pipelinePair : m_RendererPipelines)
        {
            m_ShaderLibrary->Get(pipelinePair.first)->Bind();
            for (const auto &object : pipelinePair.second)
            {
                object->Render();
            }
            m_ShaderLibrary->Get(pipelinePair.first)->Unbind();
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

    const char *vertexShaderSource = "#version 330 core\n"
                                     "layout (location = 0) in vec3 aPos;\n"
                                     "void main()\n"
                                     "{\n"
                                     "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
                                     "}\0";
    const char *fragmentShaderSource = "#version 330 core\n"
                                       "out vec4 FragColor;\n"
                                       "void main()\n"
                                       "{\n"
                                       "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
                                       "}\n\0";

    m_ShaderLibrary = std::make_unique<ShaderLibrary>();
    m_ShaderLibrary->Load("Standard", vertexShaderSource, fragmentShaderSource);

    m_RendererPipelines["Standard"].push_back(Square::GetIdentitySquare());
}

void MCEngine::Application::AddObject(const std::shared_ptr<Object> &object) { m_Objects.push_back(object); }