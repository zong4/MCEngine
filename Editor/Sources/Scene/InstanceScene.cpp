#include "InstanceScene.hpp"

MCEditor::InstanceScene::InstanceScene() : MCEngine::Scene()
{
    ENGINE_PROFILE_FUNCTION();

    m_Offsets.resize(25);
    MCEngine::Entity cubes = Add3DObject("Cubes", MCEngine::TransformComponent());
    cubes.GetComponent<MCEngine::MeshRendererComponent>().GetVAOPtr()->SetInstanceCount(m_Offsets.size());

    // Instance offsets
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            m_Offsets[i * 5 + j] = glm::translate(glm::mat4(1.0f), glm::vec3(i * 1.0f, 0.0f, j * 1.0f));
        }
    }
}

void MCEditor::InstanceScene::RenderReally() const
{
    ENGINE_PROFILE_FUNCTION();

    auto &&shader = MCEngine::ShaderLibrary::GetInstance().GetShader("Instance");
    shader->Bind();

    auto &&meshView = m_Registry.view<MCEngine::TransformComponent, MCEngine::MeshRendererComponent>();
    for (auto &&entity : meshView)
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