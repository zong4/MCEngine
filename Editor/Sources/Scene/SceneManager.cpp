#include "SceneManager.hpp"

#include "Editor/EditorConfig.hpp"
#include "EditorScene.hpp"
#include "EmptyScene.hpp"

MCEditor::SceneManager &MCEditor::SceneManager::GetInstance()
{
    static SceneManager instance;
    return instance;
}

void MCEditor::SceneManager::SetActiveScene(const std::shared_ptr<MCEngine::Scene> &scene)
{
    ENGINE_PROFILE_FUNCTION();

    m_ActiveScene = scene;
    if (m_ActiveScene)
        m_SelectedEntity = MCEngine::Entity((entt::entity)0, &m_ActiveScene->GetRegistry());
}

void MCEditor::SceneManager::NewScene()
{
    m_ActiveScene = std::make_shared<MCEditor::EmptyScene>();
    m_SelectedEntity = MCEngine::Entity((entt::entity)0, &m_ActiveScene->GetRegistry());
}

void MCEditor::SceneManager::OpenScene()
{
    const char *filters[] = {"*.mcs"};
    const char *file = tinyfd_openFileDialog("Open Scene", EditorConfig::GetInstance().GetScenesPath().c_str(), 1,
                                             filters, nullptr, 0);
    if (file)
    {
        m_ActiveScene = std::make_shared<MCEngine::Scene>();
        MCEngine::SceneSerializer::Deserialize(m_ActiveScene, file);
        m_SelectedEntity = MCEngine::Entity((entt::entity)0, &m_ActiveScene->GetRegistry());
    }
}

void MCEditor::SceneManager::SaveSceneAs() const
{
    const char *filters[] = {"*.mcs"};
    std::string defaultPath = EditorConfig::GetInstance().GetScenesPath() + m_ActiveScene->GetName() + ".mcs";
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

    NewScene();
    m_Scenes.push_back(m_ActiveScene);
}