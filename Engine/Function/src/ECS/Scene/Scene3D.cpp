#include "Scene3D.hpp"

void MCEngine::Scene3D::Render(std::shared_ptr<Camera> camera) const
{
    ENGINE_PROFILE_FUNCTION();

    auto &&shader = ShaderLibrary::GetInstanceRef().GetShader("Phong");
    shader->Bind();

    shader->SetUniformMat4("u_View", camera->GetView());
    shader->SetUniformMat4("u_Projection", camera->GetProjection());

    shader->SetUniformVec4("u_ObjectColor", glm::vec4(1.0f, 0.5f, 0.31f, 1.0f));
    shader->SetUniformVec3("u_ViewPos", camera->GetPosition());
    shader->SetUniformVec3("u_LightPos", glm::vec3(1.2f, 1.0f, 2.0f));
    shader->SetUniformVec4("u_LightColor", glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));

    auto meshView = m_Registry.view<TransformComponent, MeshRendererComponent>();
    for (auto entity : meshView)
    {
        auto &&[transform, mesh] = meshView.get<TransformComponent, MeshRendererComponent>(entity);

        shader->SetUniformMat4("u_Model", transform.GetTransformMatrix());
        shader->SetUniformVec4("u_Color", mesh.Color);
        RendererAPI::GetInstanceRef().DrawQuad(mesh.VAOPtr);
    }
}

entt::entity MCEngine::Scene3D::AddCube(TransformComponent transform, MeshRendererComponent mesh)
{
    ENGINE_PROFILE_FUNCTION();

    entt::entity entity = m_Registry.create();
    m_Registry.emplace<TransformComponent>(entity, transform);
    m_Registry.emplace<MeshRendererComponent>(entity, mesh);

    return entity;
}