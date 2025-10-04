#include "SceneManager.hpp"

#include "EditorScene.hpp"
#include "EmptyScene.hpp"

MCEditor::SceneManager &MCEditor::SceneManager::GetInstance()
{
    static SceneManager instance;
    return instance;
}

void MCEditor::SceneManager::NewScene() { m_ActiveScene = std::make_shared<MCEditor::EmptyScene>(); }

void MCEditor::SceneManager::OpenScene()
{
    const char *filters[] = {"*.mcs"};
    std::string defaultPath = std::string(PROJECT_ROOT) + "/Editor/Assets/Scenes/";
    const char *file = tinyfd_openFileDialog("Open Scene", defaultPath.c_str(), 1, filters, nullptr, 0);
    if (file)
    {
        m_ActiveScene = std::make_shared<MCEngine::Scene>();
        MCEngine::SceneSerializer::Deserialize(m_ActiveScene, file);
    }
}

void MCEditor::SceneManager::SaveSceneAs() const
{
    const char *filters[] = {"*.mcs"};
    std::string defaultPath = std::string(PROJECT_ROOT) + "/Editor/Assets/Scenes/" + m_ActiveScene->GetName() + ".mcs";
    const char *file = tinyfd_saveFileDialog("Save Scene As", defaultPath.c_str(), 1, filters, nullptr);

    if (file)
    {
        // Trim whitespace and ensure the file has the correct extension
        std::string filepath = file ? std::string(file) : "";
        filepath.erase(filepath.find_last_not_of(" \n\r\t") + 1);
        if (!filepath.empty() && filepath.substr(filepath.size() - 4) != ".mcs")
            filepath += ".mcs";

        MCEngine::SceneSerializer::Serialize(m_ActiveScene, filepath);
    }
}

MCEditor::SceneManager::SceneManager()
{
    ENGINE_PROFILE_FUNCTION();

    m_EditorScene = std::make_shared<MCEditor::EditorScene>();
    m_ActiveScene = std::make_shared<MCEditor::EmptyScene>();
}