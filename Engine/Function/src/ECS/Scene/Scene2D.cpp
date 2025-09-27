#include "Scene2D.hpp"

MCEngine::Scene2D::Scene2D()
{
    ENGINE_PROFILE_FUNCTION();

    // m_CameraEntity = m_Registry.create();
    // m_Registry.emplace<TransformComponent>(m_CameraEntity, TransformComponent());
    // m_Registry.emplace<CameraComponent>(m_CameraEntity, CameraComponent());
}

MCEngine::Scene2D::~Scene2D() {}

void MCEngine::Scene2D::Update(float deltaTime) {}

void MCEngine::Scene2D::Render(std::shared_ptr<Camera> camera) const
{
    ENGINE_PROFILE_FUNCTION();

    auto &&shader = ShaderLibrary::GetInstanceRef().GetShader("Texture");
    shader->Bind();
    shader->SetUniformMat4("u_View", camera->GetView());
    shader->SetUniformMat4("u_Projection", camera->GetProjection());

    auto spriteView = m_Registry.view<TransformComponent, SpriteRendererComponent>();
    for (auto entity : spriteView)
    {
        auto &&[transform, sprite] = spriteView.get<TransformComponent, SpriteRendererComponent>(entity);

        shader->SetUniformMat4("u_Model", transform.GetTransformMatrix());
        shader->SetUniformVec4("u_Color", sprite.Color);
        RendererAPI::GetInstanceRef().DrawQuad(sprite.VAOPtr);
    }

    auto meshView = m_Registry.view<TransformComponent, MeshRendererComponent>();
    for (auto entity : meshView)
    {
        auto &&[transform, mesh] = meshView.get<TransformComponent, MeshRendererComponent>(entity);

        shader->SetUniformMat4("u_Model", transform.GetTransformMatrix());
        shader->SetUniformVec4("u_Color", mesh.Color);
        RendererAPI::GetInstanceRef().DrawQuad(mesh.VAOPtr);
    }
}

entt::entity MCEngine::Scene2D::AddSquare(TransformComponent transform, SpriteRendererComponent sprite)
{
    ENGINE_PROFILE_FUNCTION();

    entt::entity entity = m_Registry.create();
    m_Registry.emplace<TransformComponent>(entity, transform);
    m_Registry.emplace<SpriteRendererComponent>(entity, sprite);

    return entity;
}

entt::entity MCEngine::Scene2D::AddCube(TransformComponent transform, MeshRendererComponent mesh)
{
    ENGINE_PROFILE_FUNCTION();

    entt::entity entity = m_Registry.create();
    m_Registry.emplace<TransformComponent>(entity, transform);
    m_Registry.emplace<MeshRendererComponent>(entity, mesh);

    return entity;
}