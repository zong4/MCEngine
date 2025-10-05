#include "Editor.hpp"

#include "Layer/EditorLayer.hpp"
#include "Manager/AssetsManager.hpp"
#include "Manager/ConfigManager.hpp"
#include "Manager/SceneManager.hpp"

MCEditor::Editor::Editor(const MCEngine::WindowProperty &props) : Application(props)
{
    ENGINE_PROFILE_FUNCTION();

    ConfigManager::GetInstance(); // Initialize editor config
    AssetsManager::GetInstance(); // Initialize assets manager
    SceneManager::GetInstance();  // Initialize scene manager

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