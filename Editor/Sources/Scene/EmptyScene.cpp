#include "EmptyScene.hpp"

MCEditor::EmptyScene::EmptyScene()
{
    m_MainCamera = AddCamera("MainCamera",
                             MCEngine::TransformComponent(glm::vec3(0.0f, 5.0f, 8.0f), glm::vec3(-30.0f, 0.0f, 0.0f)),
                             MCEngine::CameraComponent(MCEngine::CameraType::Perspective));

    // todo: Welcome to MC Engine!
}