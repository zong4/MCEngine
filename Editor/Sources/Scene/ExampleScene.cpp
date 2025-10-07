#include "ExampleScene.hpp"

MCEditor::ExampleScene::ExampleScene()
{
    m_MainCamera = AddCamera("MainCamera",
                             MCEngine::TransformComponent(glm::vec3(0.0f, 5.0f, 8.0f), glm::vec3(-30.0f, 0.0f, 0.0f)),
                             MCEngine::CameraComponent(MCEngine::CameraType::Perspective));

    // Welcome to MC Engine!
    int size = 9;
    float center = size / 2.0f;
    MCEngine::Entity cubes = AddEmptyEntity("Cubes");
    for (int x = 0; x < size; x++)
    {
        for (int y = 0; y < size; y++)
        {
            for (int z = 0; z < size; z++)
            {
                MCEngine::Entity cube = Add3DObject(
                    "Cube" + std::to_string(x) + std::to_string(y) + std::to_string(z),
                    MCEngine::TransformComponent(glm::vec3(x - center, y - center, z - center)),
                    MCEngine::MeshRendererComponent(MCEngine::VAOLibrary::GetInstance().GetVAO("Cube"),
                                                    MCEngine::ShaderLibrary::GetInstance().GetShader("ShowColor")));
                cube.GetComponent<MCEngine::RelationshipComponent>().SetParent(cubes);
                cubes.GetComponent<MCEngine::RelationshipComponent>().AddChild(cube);
            }
        }
    }
}