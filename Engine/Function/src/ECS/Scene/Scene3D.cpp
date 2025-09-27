#include "Scene3D.hpp"

void MCEngine::Scene3D::Render(std::shared_ptr<Camera> camera) const
{
    ENGINE_PROFILE_FUNCTION();

    auto &&shader = ShaderLibrary::GetInstanceRef().GetShader("Texture");
    shader->Bind();
    shader->SetUniformMat4("u_View", camera->GetView());
    shader->SetUniformMat4("u_Projection", camera->GetProjection());

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