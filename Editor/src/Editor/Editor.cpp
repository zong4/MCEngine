#include "Editor.hpp"

MCEditor::Editor::Editor(const MCEngine::WindowProps &props) : Application(props)
{
    ENGINE_PROFILE_FUNCTION();

    AddLayer(std::make_shared<EditorLayer>(m_WindowPtr));

    LOG_EDITOR_INFO("Editor created.");
}

MCEditor::Editor::~Editor() { LOG_EDITOR_INFO("Editor destroyed."); }

std::unique_ptr<MCEngine::Application> MCEngine::CreateApplication()
{
    ENGINE_PROFILE_FUNCTION();

    return std::make_unique<MCEditor::Editor>(
        MCEngine::WindowProps("Minecraft Engine", 1280, 720, true, new float[4]{0.1f, 0.1f, 0.1f, 1.0f}));
}