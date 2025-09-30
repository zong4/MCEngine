#include "SampleScene.hpp"

MCEditor::SampleScene::SampleScene() : MCEngine::Scene()
{
    ENGINE_PROFILE_FUNCTION();

    // 2D
    {
        entt::entity squareEntity = MCEngine::EntityFactory::CreateSquare(
            m_Registry, "Square", glm::vec3(0.0f), glm::vec3(0.0f), glm::vec3(5.0f), glm::vec4(1.0f),
            MCEngine::Texture2DLibrary::GetInstance().GetTexture("02BG"));
    }

    // 3D
    {
        entt::entity cubes = MCEngine::EntityFactory::CreateEmptyEntity(m_Registry, "Cubes");
        for (int i = 0; i < 5; i++)
        {
            for (int j = 0; j < 5; j++)
            {
                entt::entity cubeEntity =
                    MCEngine::EntityFactory::CreateCube(m_Registry, "Cube", glm::vec3(i * 1.0f, 0.0f, j * 1.0f));
                m_Registry.get<MCEngine::RelationshipComponent>(cubeEntity).SetParent(cubes);
                m_Registry.get<MCEngine::RelationshipComponent>(cubes).AddChild(cubeEntity);
            }
        }

        // Default light
        {
            entt::entity light = MCEngine::EntityFactory::CreateDirectionalLight(m_Registry, "DirectionalLight");
            MCEngine::EntityFactory::AddComponents(
                m_Registry, light,
                MCEngine::MeshRendererComponent(MCEngine::VAOLibrary::GetInstance().GetVAO("Cube"),
                                                MCEngine::Material(glm::vec4(1.0f), 0.3f, 1.0f, 0.5f, 32.0f)));
        }
        {
            entt::entity light = MCEngine::EntityFactory::CreatePointLight(m_Registry, "PointLight");
            MCEngine::EntityFactory::AddComponents(
                m_Registry, light,
                MCEngine::MeshRendererComponent(MCEngine::VAOLibrary::GetInstance().GetVAO("Cube"),
                                                MCEngine::Material(glm::vec4(1.0f), 0.3f, 1.0f, 0.5f, 32.0f)));
        }
        {
            entt::entity light = MCEngine::EntityFactory::CreateSpotLight(m_Registry, "SpotLight");
            MCEngine::EntityFactory::AddComponents(
                m_Registry, light,
                MCEngine::MeshRendererComponent(MCEngine::VAOLibrary::GetInstance().GetVAO("Cube"),
                                                MCEngine::Material(glm::vec4(1.0f), 0.3f, 1.0f, 0.5f, 32.0f)));
        }

        // Skybox
        {
            entt::entity skybox = MCEngine::EntityFactory::CreateEmptyEntity(m_Registry, "Skybox");
            MCEngine::EntityFactory::AddComponents(
                m_Registry, skybox,
                MCEngine::SkyboxComponent(std::string(PROJECT_ROOT) + "/Engine/Assets/Images/skybox"));
        }
    }
}