#include "Editor.hpp"

#include "EditorLayer.hpp"

MCEditor::Editor::Editor(MCEngine::WindowProps props) : Application(props)
{
    ENGINE_PROFILE_FUNCTION();

    AddLayer(std::make_shared<MCEngine::EditorLayer>());
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