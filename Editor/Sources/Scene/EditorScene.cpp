#include "EditorScene.hpp"

#include "Script/CameraController.hpp"

MCEditor::EditorScene::EditorScene() : MCEngine::Scene()
{
    ENGINE_PROFILE_FUNCTION();

    m_MainCamera = AddCamera("MainCamera",
                             MCEngine::TransformComponent(glm::vec3(0.0f, 10.0f, 20.0f), glm::vec3(-30.0f, 0.0f, 0.0f)),
                             MCEngine::CameraComponent(MCEngine::CameraType::Perspective));
    m_MainCamera.AddComponent<MCEngine::NativeScriptComponent>().Bind<CameraController>();
}