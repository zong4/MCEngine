#include "ExampleScene.hpp"

MCEditor::ExampleScene::ExampleScene()
{
    m_MainCamera = AddCamera("MainCamera",
                             MCEngine::TransformComponent(glm::vec3(0.0f, 5.0f, 8.0f), glm::vec3(-30.0f, 0.0f, 0.0f)),
                             MCEngine::CameraComponent(MCEngine::CameraType::Perspective));

    AddLight("DirectionalLight",
             MCEngine::TransformComponent(glm::vec3(0.0f, 10.0f, 0.0f), glm::vec3(-45.0f, -45.0f, 0.0f)),
             MCEngine::LightComponent(MCEngine::LightType::Directional));

    WelcomeToMCEngine();
}

void MCEditor::ExampleScene::WelcomeToMCEngine()
{
    ENGINE_PROFILE_FUNCTION();

    struct Position
    {
        int x, y, z;

        bool operator<(const Position &other) const
        {
            if (x != other.x)
                return x < other.x;
            if (y != other.y)
                return y < other.y;
            return z < other.z;
        }
    };

    std::set<Position> positions = {
        {0, 0, 2}, {0, 0, 3}, {0, 0, 4}, {0, 0, 5}, {0, 0, 6},
    };

    int size = 9;
    float center = size / 2.0f;
    MCEngine::Entity cubes = AddEmptyEntity("Cubes");
    for (int x = 0; x < size; x++)
    {
        for (int y = 0; y < size; y++)
        {
            for (int z = 0; z < size; z++)
            {
                if (positions.find({x, y, z}) != positions.end())
                    continue;

                MCEngine::Entity cube = Add3DObject(
                    "Cube" + std::to_string(x) + std::to_string(y) + std::to_string(z),
                    MCEngine::TransformComponent(glm::vec3(x - center, y - center, z - center)),
                    MCEngine::MeshRendererComponent(MCEngine::VAOLibrary::GetInstance().GetVAO("Cube"),
                                                    MCEngine::ShaderLibrary::GetInstance().GetShader("BlinnPhong")));
                cube.GetComponent<MCEngine::RelationshipComponent>().SetParent(cubes);
                cubes.GetComponent<MCEngine::RelationshipComponent>().AddChild(cube);
            }
        }
    }
}