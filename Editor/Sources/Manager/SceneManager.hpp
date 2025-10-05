#pragma once

#include <Function.hpp>

namespace MCEditor
{

class SceneManager
{
public:
    static SceneManager &GetInstance();

    // Getters
    MCEngine::Entity &GetSelectedEntity() { return m_SelectedEntity; }
    MCEngine::Entity GetSelectedEntity() const { return m_SelectedEntity; }
    std::shared_ptr<MCEngine::Scene> GetEditorScene() const { return m_EditorScene; }
    std::shared_ptr<MCEngine::Scene> GetActiveScene() const { return m_ActiveScene; }

    // Setters
    void SetActiveScene(const std::shared_ptr<MCEngine::Scene> &scene);

public:
    void NewExampleScene();
    void OpenScene(std::string filepath);
    void OpenSceneDialog();
    void SaveSceneAsDialog() const;

private:
    MCEngine::Entity m_SelectedEntity;
    std::shared_ptr<MCEngine::Scene> m_EditorScene;
    std::shared_ptr<MCEngine::Scene> m_ActiveScene; // todo: add active bool in scene class
    std::vector<std::shared_ptr<MCEngine::Scene>> m_Scenes;

private:
    SceneManager();
    ~SceneManager() = default;

    void NewEmptyScene();
};

} // namespace MCEditor