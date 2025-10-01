#include "InstanceScene.hpp"

MCEditor::InstanceScene::InstanceScene() : MCEngine::Scene()
{
    ENGINE_PROFILE_FUNCTION();

    entt::entity cubes = MCEngine::EntityFactory::CreateCube(m_Registry, "Cubes");

    m_Offsets.resize(25);
    m_Registry.get<MCEngine::MeshRendererComponent>(cubes).GetVAOPtr()->SetInstanceCount(m_Offsets.size());

    // Instance offsets
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            m_Offsets[i * 5 + j] = glm::translate(glm::mat4(1.0f), glm::vec3(i * 1.0f, 0.0f, j * 1.0f));
        }
    }
}

void MCEditor::InstanceScene::Render(MCEngine::CameraComponent &camera) const
{
    ENGINE_PROFILE_FUNCTION();

    MCEngine::Scene::Render(camera);

    auto &&shader = MCEngine::ShaderLibrary::GetInstance().GetShader("Instance");
    shader->Bind();

    auto &&meshView = m_Registry.view<MCEngine::TransformComponent, MCEngine::MeshRendererComponent>();
    for (auto entity : meshView)
    {
        auto &&[transform, mesh] = meshView.get<MCEngine::TransformComponent, MCEngine::MeshRendererComponent>(entity);

        for (int instanceCount = 0; instanceCount < m_Offsets.size(); instanceCount++)
        {
            shader->SetUniformMat4("u_Models[" + std::to_string(instanceCount) + "]",
                                   m_Offsets[instanceCount] * transform.GetTransformMatrix());
            mesh.GetMaterial().Bind(shader, "u_Material");
        }

        mesh.GetVAOPtr()->Render();
    }

    shader->Unbind();
}