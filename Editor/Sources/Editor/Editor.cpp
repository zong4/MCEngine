#include "Editor.hpp"

#include "EditorConfig.hpp"
#include "EditorLayer.hpp"

MCEditor::Editor::Editor(const MCEngine::WindowProperty &props) : Application(props)
{
    ENGINE_PROFILE_FUNCTION();

    AddLayer(std::make_shared<EditorLayer>(m_Window));

    LOG_EDITOR_INFO("Editor created");
}

MCEditor::Editor::~Editor() { LOG_EDITOR_INFO("Editor destroyed"); }

std::unique_ptr<MCEngine::Application> MCEngine::CreateApplication()
{
    ENGINE_PROFILE_FUNCTION();

    return std::make_unique<MCEditor::Editor>(
        MCEngine::WindowProperty("Minecraft Engine", 1280, 720, true, glm::vec4(0.0f, 0.0f, 0.0f, 1.0f)));
}