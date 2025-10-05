#include "SceneManager.hpp"

#include "Editor/EditorConfig.hpp"
#include "EditorScene.hpp"
#include "ExampleScene.hpp"

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

void MCEditor::SceneManager::NewExampleScene()
{
    ENGINE_PROFILE_FUNCTION();

    SetActiveScene(std::make_shared<MCEditor::ExampleScene>());
}

void MCEditor::SceneManager::OpenScene(std::string filepath)
{
    NewEmptyScene();
    MCEngine::SceneSerializer::Deserialize(m_ActiveScene, filepath);
    SetActiveScene(m_ActiveScene);
}

void MCEditor::SceneManager::OpenSceneDialog()
{
    const char *filters[] = {"*.mcsene"};
    const char *file = tinyfd_openFileDialog("Open Scene", EditorConfig::GetInstance().GetScenesPath().c_str(), 1,
                                             filters, nullptr, 0);
    if (file)
    {
        NewEmptyScene();
        MCEngine::SceneSerializer::Deserialize(m_ActiveScene, file);
        SetActiveScene(m_ActiveScene);
    }
}

void MCEditor::SceneManager::SaveSceneAsDialog() const
{
    const char *filters[] = {"*.mcsene"};
    std::string defaultPath = EditorConfig::GetInstance().GetScenesPath() + m_ActiveScene->GetName() + ".mcsene";
    const char *file = tinyfd_saveFileDialog("Save Scene As", defaultPath.c_str(), 1, filters, nullptr);

    if (file)
    {
        // Trim whitespace and ensure the file has the correct extension
        std::string filepath = file ? std::string(file) : "";
        filepath.erase(filepath.find_last_not_of(" \n\r\t") + 1);
        if (!filepath.empty() && filepath.substr(filepath.size() - 4) != ".mcsene")
            filepath += ".mcsene";

        MCEngine::SceneSerializer::Serialize(m_ActiveScene, filepath);
    }
}

MCEditor::SceneManager::SceneManager()
{
    ENGINE_PROFILE_FUNCTION();

    m_EditorScene = std::make_shared<MCEditor::EditorScene>();

    NewExampleScene();
    m_Scenes.push_back(m_ActiveScene);
}

void MCEditor::SceneManager::NewEmptyScene()
{
    ENGINE_PROFILE_FUNCTION();

    SetActiveScene(std::make_shared<MCEngine::Scene>());
}