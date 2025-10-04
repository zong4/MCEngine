#pragma once

#include <Function.hpp>

namespace MCEditor
{

class SceneManager
{
public:
    static SceneManager &GetInstance();

    // Getters
    std::shared_ptr<MCEngine::Scene> GetEditorScene() const { return m_EditorScene; }
    std::shared_ptr<MCEngine::Scene> GetActiveScene() const { return m_ActiveScene; }

    // Setters
    void SetActiveScene(const std::shared_ptr<MCEngine::Scene> &scene) { m_ActiveScene = scene; }

public:
    void NewScene();
    void OpenScene();
    void SaveSceneAs() const;

private:
    std::shared_ptr<MCEngine::Scene> m_EditorScene;
    std::shared_ptr<MCEngine::Scene> m_ActiveScene; // todo: add active bool in scene class
    std::vector<std::shared_ptr<MCEngine::Scene>> m_Scenes;

private:
    SceneManager();
    ~SceneManager() = default;
};

} // namespace MCEditor