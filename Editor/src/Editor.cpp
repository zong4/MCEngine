#include "Editor.hpp"

MCEditor::Editor::Editor(MCEngine::WindowProps props) : Application(props)
{
    AddLayer(std::make_shared<MCEngine::CameraLayer>());

    AddLayer(std::make_shared<MCEngine::ImGuiLayer>(m_Window));

    LOG_EDITOR_INFO("Editor created.");
}

MCEditor::Editor::~Editor() { LOG_EDITOR_INFO("Editor destroyed."); }

std::unique_ptr<MCEngine::Application> MCEngine::CreateApplication()
{
    return std::make_unique<MCEditor::Editor>(
        MCEngine::WindowProps(800, 600, "Minecraft Engine", true, new float[4]{0.1f, 0.1f, 0.1f, 1.0f}));
}