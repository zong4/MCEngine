#include "Scene3D.hpp"

MCEngine::Scene3D::Scene3D()
{
    ENGINE_PROFILE_FUNCTION();

    // Default light
    m_Light = m_Registry.create();
    m_Registry.emplace<TransformComponent>(m_Light, TransformComponent(glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.0f)));
    m_Registry.emplace<LightComponent>(m_Light, LightComponent(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), 1.0f));
}

void MCEngine::Scene3D::Render(const std::shared_ptr<Camera> &camera) const
{
    ENGINE_PROFILE_FUNCTION();

    auto &&shader = ShaderLibrary::GetInstance().GetShader("BlinnPhong");
    shader->Bind();

    // Camera
    shader->SetUniformVec3("u_ViewPos", camera->GetPosition());
    shader->SetUniformMat4("u_View", camera->GetView());
    shader->SetUniformMat4("u_Projection", camera->GetProjection());

    // Light
    shader->SetUniformVec3("u_LightPos", m_Registry.get<TransformComponent>(m_Light).Position);
    shader->SetUniformVec4("u_LightColor", m_Registry.get<LightComponent>(m_Light).Color);

    auto meshView = m_Registry.view<TransformComponent, MeshRendererComponent>();
    for (auto entity : meshView)
    {
        auto &&[transform, mesh] = meshView.get<TransformComponent, MeshRendererComponent>(entity);

        // Transform component
        shader->SetUniformMat4("u_Model", transform.GetTransformMatrix());

        // Mesh component
        shader->SetUniformVec4("u_ObjectColor", mesh.Color);

        RendererAPI::GetInstance().DrawQuad(mesh.VAOPtr);
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