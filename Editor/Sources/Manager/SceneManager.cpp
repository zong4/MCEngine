#include "SceneManager.hpp"

#include "Manager/ConfigManager.hpp"
#include "Scene/EditorScene.hpp"
#include "Scene/ExampleScene.hpp"

MCEditor::SceneManager &MCEditor::SceneManager::GetInstance()
{
    static SceneManager instance;
    return instance;
}

void MCEditor::SceneManager::SetSelectedEntity(entt::entity entity)
{
    ENGINE_PROFILE_FUNCTION();

    m_SelectedEntity = MCEngine::Entity(entity, &m_ActiveScene->GetRegistry());
}

void MCEditor::SceneManager::SetActiveScene(const std::shared_ptr<MCEngine::Scene> &scene)
{
    ENGINE_PROFILE_FUNCTION();

    m_ActiveScene = scene;
    // if (m_ActiveScene)
    //     m_SelectedEntity = MCEngine::Entity((entt::entity)0, &m_ActiveScene->GetRegistry());
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
    const char *filters[] = {"*.mcscene"};
    const char *file = tinyfd_openFileDialog(
        "Open Scene", ConfigManager::GetInstance().GetScenesPath().string().c_str(), 1,
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
    const char *filters[] = {"*.mcscene"};
    std::string defaultPath = (ConfigManager::GetInstance().GetScenesPath() / (m_ActiveScene->GetName() + ".mcscene")).string();
    const char *filepath = tinyfd_saveFileDialog("Save Scene As", defaultPath.c_str(), 1, filters, nullptr);

    if (filepath)
    {
        std::string file = filepath;
        if (std::filesystem::path(file).extension() != ".mcscene")
            file += ".mcscene";

        MCEngine::SceneSerializer::Serialize(m_ActiveScene, file);
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