#include "Scene2D.hpp"

void MCEngine::Scene2D::Render(std::shared_ptr<Camera> camera) const
{
    ENGINE_PROFILE_FUNCTION();

    auto &&shader = ShaderLibrary::GetInstance().GetShader("Texture");
    shader->Bind();

    // Camera
    shader->SetUniformMat4("u_View", camera->GetView());
    shader->SetUniformMat4("u_Projection", camera->GetProjection());

    auto spriteView = m_Registry.view<TransformComponent, SpriteRendererComponent>();
    for (auto entity : spriteView)
    {
        auto &&[transform, sprite] = spriteView.get<TransformComponent, SpriteRendererComponent>(entity);

        // Transform component
        shader->SetUniformMat4("u_Model", transform.GetTransformMatrix());

        // Sprite component
        shader->SetUniformVec4("u_Color", sprite.Color);
        shader->SetUniformInt("u_Texture", 0);
        sprite.TexturePtr->Bind(0);

        RendererAPI::GetInstance().DrawQuad(sprite.VAOPtr);
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