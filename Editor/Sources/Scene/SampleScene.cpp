#include "SampleScene.hpp"

MCEditor::SampleScene::SampleScene()
{
    entt::entity m_Light = MCEngine::EntityFactory::CreateDirectionalLight(m_Registry, "DirectionalLight");

    MCEngine::EntityFactory::CreateCube(m_Registry, "Cube");
}

void MCEditor::SampleScene::Render(MCEngine::CameraComponent &camera) const
{
    ENGINE_PROFILE_FUNCTION();

    MCEngine::Scene::Render(camera);
}

void MCEditor::SampleScene::RenderShadowMap() const
{

    auto &&shader = MCEngine::ShaderLibrary::GetInstance().GetShader("ShadowMap");
    shader->Bind();

    // todo
    {
        glm::vec3 position = m_Registry.get<MCEngine::TransformComponent>(m_Light).GetPosition();
        glm::vec3 rotation = m_Registry.get<MCEngine::TransformComponent>(m_Light).GetRotation();

        glm::mat4 rotationX = glm::rotate(glm::mat4(1.0f), glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
        glm::mat4 rotationY = glm::rotate(glm::mat4(1.0f), glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
        glm::mat4 rotationZ = glm::rotate(glm::mat4(1.0f), glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
        glm::mat4 rotationXYZ = rotationZ * rotationY * rotationX;

        glm::vec3 front = glm::normalize(glm::vec3(rotationXYZ * glm::vec4(0.0f, 0.0f, -1.0f, 0.0f)));
        glm::vec3 up = glm::normalize(glm::vec3(rotationXYZ * glm::vec4(0.0f, 1.0f, 0.0f, 0.0f)));
        shader->SetUniformMat4("u_LightView", glm::lookAt(position, position + front, up));
    }
    shader->SetUniformMat4("u_LightProjection", glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, 1.0f, 20.0f));

    auto &&meshView = m_Registry.view<MCEngine::TransformComponent, MCEngine::MeshRendererComponent>();
    for (auto &&entity : meshView)
    {
        auto &&[transform, mesh] = meshView.get<MCEngine::TransformComponent, MCEngine::MeshRendererComponent>(entity);

        // transform
        shader->SetUniformMat4("u_Model", transform.GetTransformMatrix());

        // mesh
        mesh.GetVAOPtr()->Render(MCEngine::RendererType::Triangles);
    }

    shader->Unbind();
}