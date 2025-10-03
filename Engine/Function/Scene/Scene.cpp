#include "Scene.hpp"

#include <imgui.h>

MCEngine::Scene::Scene()
{
    ENGINE_PROFILE_FUNCTION();

    m_MainCamera = AddPerspectiveCamera("MainCamera");
}

MCEngine::Scene::~Scene()
{
    ENGINE_PROFILE_FUNCTION();

    m_Registry.view<MCEngine::NativeScriptComponent>().each(
        [&](auto &&entity, auto &&nsc) { nsc.Instance->OnDestroy(); });
}

void MCEngine::Scene::Update(float deltaTime)
{
    ENGINE_PROFILE_FUNCTION();

    auto &&view = m_Registry.view<TransformComponent, RelationshipComponent>();
    for (auto &&entity : view)
    {
        auto [transform, relationship] = view.get<TransformComponent, RelationshipComponent>(entity);
        if (!relationship.GetParent())
        {
            transform.UpdateTransformMatrix(glm::mat4(1.0f), relationship);
            transform.UpdateViewMatrix();
        }
    }

    m_Registry.view<MCEngine::NativeScriptComponent>().each([&](auto &&entity, auto &&nsc) {
        if (!nsc.Instance)
        {
            nsc.Instance = nsc.InstantiateScript();
            nsc.Instance->SetEntity(MCEngine::Entity{entity, &m_Registry});
            nsc.Instance->OnCreate();
            nsc.Instance->OnStart();
        }
        nsc.Instance->OnUpdate(deltaTime);
    });
}

void MCEngine::Scene::RenderShadowMap() const
{
    ENGINE_PROFILE_FUNCTION();

    m_ShadowMapPtr->Bind();
    RendererCommand::ClearDepthBuffer();

    RenderShadowMapReally();

    m_ShadowMapPtr->Unbind();
}

void MCEngine::Scene::Render(const Entity &camera) const
{
    ENGINE_PROFILE_FUNCTION();

    UniformBufferLibrary::GetInstance().UpdateUniformBuffer(
        "UniformBuffer0",
        {
            {glm::value_ptr(camera.GetComponent<TransformComponent>().GetViewMatrix()), sizeof(glm::mat4), 0},
            {glm::value_ptr(camera.GetComponent<CameraComponent>().GetProjectionMatrix()), sizeof(glm::mat4),
             sizeof(glm::mat4)},
            {glm::value_ptr(camera.GetComponent<TransformComponent>().GetPosition()), sizeof(glm::vec3),
             sizeof(glm::mat4) + sizeof(glm::mat4)},
        });

    // 2D
    {
        auto &&shader = MCEngine::ShaderLibrary::GetInstance().GetShader("Texture");
        shader->Bind();

        auto &&spriteView = m_Registry.view<MCEngine::TransformComponent, MCEngine::SpriteRendererComponent>();
        for (auto &&entity : spriteView)
        {
            auto &&[transform, sprite] =
                spriteView.get<MCEngine::TransformComponent, MCEngine::SpriteRendererComponent>(entity);

            shader->SetUniformMat4("u_Model", transform.GetTransformMatrix());
            shader->SetUniformVec4("u_Color", sprite.GetColor());
            shader->SetUniformInt("u_Texture", 0);
            sprite.GetTexturePtr()->Bind(0);

            sprite.GetVAOPtr()->Render();
        }

        shader->Unbind();
    }

    RenderReally();
}

void MCEngine::Scene::Resize(float width, float height)
{
    ENGINE_PROFILE_FUNCTION();

    auto &&view = m_Registry.view<CameraComponent>();
    for (auto &&entity : view)
    {
        auto &&camera = view.get<CameraComponent>(entity);
        camera.Resize(width, height);
    }
}

MCEngine::Entity MCEngine::Scene::AddEmptyEntity(const std::string &name, const TransformComponent &transform)
{
    ENGINE_PROFILE_FUNCTION();

    Entity entity{m_Registry.create(), &m_Registry};
    entity.AddComponent<TagComponent>(name);
    entity.AddComponent<TransformComponent>(transform);
    entity.AddComponent<RelationshipComponent>();
    return entity;
}

MCEngine::Entity MCEngine::Scene::AddSquare(const std::string &name, const TransformComponent &transform,
                                            const glm::vec4 &color, const std::shared_ptr<Texture2D> &texturePtr)
{
    Entity entity = AddEmptyEntity(name, transform);
    entity.AddComponent<SpriteRendererComponent>(MCEngine::VAOLibrary::GetInstance().GetVAO("Square"), color,
                                                 texturePtr);
    return entity;
}

MCEngine::Entity MCEngine::Scene::AddCube(const std::string &name, const TransformComponent &transform,
                                          const std::shared_ptr<Shader> &shaderPtr, const Material &material)
{
    Entity entity = AddEmptyEntity(name, transform);
    entity.AddComponent<MeshRendererComponent>(MCEngine::VAOLibrary::GetInstance().GetVAO("Cube"), shaderPtr, material);
    return entity;
}

MCEngine::Entity MCEngine::Scene::AddOrthoCamera(const std::string &name, const TransformComponent &transform)
{
    Entity entity = AddEmptyEntity(name, transform);
    entity.AddComponent<CameraComponent>(CameraType::Orthographic);
    return entity;
}

MCEngine::Entity MCEngine::Scene::AddPerspectiveCamera(const std::string &name, const TransformComponent &transform)
{
    Entity entity = AddEmptyEntity(name, transform);
    entity.AddComponent<CameraComponent>(CameraType::Perspective);
    return entity;
}

MCEngine::Entity MCEngine::Scene::AddDirectionalLight(const std::string &name, const TransformComponent &transform,
                                                      const glm::vec3 &color, float intensity)
{
    Entity entity = AddEmptyEntity(name, transform);
    entity.AddComponent<LightComponent>(color, intensity);
    return entity;
}

MCEngine::Entity MCEngine::Scene::AddPointLight(const std::string &name, const TransformComponent &transform,
                                                const glm::vec3 &color, float intensity, float constant, float linear,
                                                float quadratic)
{
    Entity entity = AddEmptyEntity(name, transform);
    entity.AddComponent<LightComponent>(color, intensity, constant, linear, quadratic);
    return entity;
}

MCEngine::Entity MCEngine::Scene::AddSpotLight(const std::string &name, const TransformComponent &transform,
                                               const glm::vec3 &color, float intensity, float constant, float linear,
                                               float quadratic, float cutOff, float outerCutOff)
{
    Entity entity = AddEmptyEntity(name, transform);
    entity.AddComponent<LightComponent>(color, intensity, constant, linear, quadratic, cutOff, outerCutOff);
    return entity;
}