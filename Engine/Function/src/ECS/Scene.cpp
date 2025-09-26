#include "Scene.hpp"

MCEngine::Scene::Scene() { CreateEntity(); }

MCEngine::Scene::~Scene() {}

void MCEngine::Scene::Update(float deltaTime) {}

void MCEngine::Scene::Render(std::shared_ptr<Camera> camera) const
{
    ENGINE_PROFILE_FUNCTION();

    auto &&shader = ShaderLibrary::GetInstance().GetShader("Standard");
    shader->Bind();
    shader->SetUniformMat4("u_View", camera->GetView());
    shader->SetUniformMat4("u_Projection", camera->GetProjection());
    shader->SetUniformMat4("u_Model", glm::mat4(1.0f));
    shader->SetUniformVec4("u_Color", glm::vec4(1.0f));

    auto view = m_Registry.view<TransformComponent, SpriteRendererComponent>();
    for (auto entity : view)
    {
        auto &&[transform, sprite] = view.get<TransformComponent, SpriteRendererComponent>(entity);
        RendererAPI::GetInstance().DrawQuad(transform.GetTransformMatrix(), sprite.Color);
    }
}

entt::entity MCEngine::Scene::CreateEntity()
{
    ENGINE_PROFILE_FUNCTION();

    entt::entity entity = m_Registry.create();
    m_Registry.emplace<TransformComponent>(entity);
    m_Registry.emplace<SpriteRendererComponent>(entity);

    return entity;
}