#include "Editor.hpp"

#include "EditorLayer.hpp"

MCEditor::Editor::Editor(MCEngine::WindowProps props) : Application(props)
{
    ENGINE_PROFILE_FUNCTION();

    float width = (float)m_WindowPtr->GetProps().Width;
    float height = (float)m_WindowPtr->GetProps().Height;

    AddLayer(std::make_shared<MCEngine::EditorLayer>(
        std::make_shared<MCEngine::OrthoCamera>(glm::vec3(width / 100.0f, height / 100.0f, 10.0f)),
        std::make_shared<MCEngine::PerspectiveCamera>(45.0f, width / height, 0.1f, 100.0f,
                                                      glm::vec3(0.0f, 0.0f, 10.0f))));

    AddLayer(std::make_shared<MCEngine::ImGuiLayer>(m_WindowPtr));

    LOG_EDITOR_INFO("Editor created.");
}

MCEditor::Editor::~Editor() { LOG_EDITOR_INFO("Editor destroyed."); }

std::unique_ptr<MCEngine::Application> MCEngine::CreateApplication()
{
    ENGINE_PROFILE_FUNCTION();

    return std::make_unique<MCEditor::Editor>(
        MCEngine::WindowProps(800, 450, "Minecraft Engine", true, new float[4]{0.1f, 0.1f, 0.1f, 1.0f}));
}