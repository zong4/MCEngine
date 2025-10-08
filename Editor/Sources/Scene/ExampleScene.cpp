#include "ExampleScene.hpp"

MCEditor::ExampleScene::ExampleScene()
{
    m_MainCamera = AddCamera("MainCamera",
                             MCEngine::TransformComponent(glm::vec3(0.0f, 5.0f, 8.0f), glm::vec3(-30.0f, 0.0f, 0.0f)),
                             MCEngine::CameraComponent(MCEngine::CameraType::Perspective));

    AddLight("DirectionalLight",
             MCEngine::TransformComponent(glm::vec3(0.0f, 10.0f, 0.0f), glm::vec3(-45.0f, -45.0f, 0.0f)),
             MCEngine::LightComponent(MCEngine::LightType::Directional));

    AddSkybox("Skybox", MCEngine::SkyboxComponent());

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
        {0, 0, 2}, {0, 0, 3}, {0, 0, 4}, {0, 0, 5}, {0, 0, 6},                       // M
        {0, 1, 2}, {0, 1, 3}, {0, 1, 4}, {0, 1, 5}, {0, 1, 6},                       // M
        {0, 2, 2}, {0, 2, 3}, {0, 2, 4}, {0, 2, 5}, {0, 2, 6},                       // M
        {0, 3, 2}, {0, 3, 3}, {0, 3, 5}, {0, 3, 6},                                  // M
        {0, 4, 2}, {0, 4, 6},                                                        // M
        {0, 5, 4},                                                                   // M
        {0, 6, 3}, {0, 6, 4}, {0, 6, 5},                                             // M
        {0, 7, 2}, {0, 7, 3}, {0, 7, 4}, {0, 7, 5}, {0, 7, 6},                       // M
        {0, 8, 1}, {0, 8, 2}, {0, 8, 3}, {0, 8, 4}, {0, 8, 5}, {0, 8, 6}, {0, 8, 7}, // M

        {1, 0, 2}, {1, 0, 3}, {1, 0, 4}, {1, 0, 5}, {1, 0, 6},                       // M
        {1, 1, 2}, {1, 1, 3}, {1, 1, 4}, {1, 1, 5}, {1, 1, 6},                       // M
        {1, 2, 2}, {1, 2, 3}, {1, 2, 4}, {1, 2, 5}, {1, 2, 6},                       // M
        {1, 3, 2}, {1, 3, 3}, {1, 3, 5}, {1, 3, 6},                                  // M
        {1, 4, 2}, {1, 4, 6},                                                        // M
        {1, 5, 4},                                                                   // M
        {1, 6, 3}, {1, 6, 4}, {1, 6, 5},                                             // M
        {1, 7, 2}, {1, 7, 3}, {1, 7, 4}, {1, 7, 5}, {1, 7, 6},                       // M
        {1, 8, 1}, {1, 8, 2}, {1, 8, 3}, {1, 8, 4}, {1, 8, 5}, {1, 8, 6}, {1, 8, 7}, // M
    };

    int size = 9;
    float center = size / 2.0f;
    MCEngine::Entity cubes = AddEmptyEntity(
        "Cubes", MCEngine::TransformComponent(glm::vec3(0.0f), glm::vec3(0, 45.0f, 0.0f), glm::vec3(1.0f)));
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