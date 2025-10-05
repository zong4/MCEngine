#include "Scene.hpp"

#include <imgui.h>

MCEngine::Scene::~Scene()
{
    ENGINE_PROFILE_FUNCTION();

    m_Registry.view<MCEngine::NativeScriptComponent>().each([&](auto &&entity, auto &&nsc) { nsc.DestroyScript(); });
}

void MCEngine::Scene::Update(float deltaTime)
{
    ENGINE_PROFILE_FUNCTION();

    // Update all transform matrices
    auto &&view = m_Registry.view<TransformComponent, RelationshipComponent>();
    for (auto &&entity : view)
    {
        auto &&[transform, relationship] = view.get<TransformComponent, RelationshipComponent>(entity);
        if (!relationship.GetParent())
        {
            transform.UpdateTransformMatrix(glm::mat4(1.0f), relationship);
            transform.UpdateViewMatrix();
        }
    }

    // Update all scripts
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

    if (!m_MainLight)
        return;

    m_ShadowMap->Bind();
    RendererCommand::ClearDepthBuffer();
    auto &&shader = MCEngine::ShaderLibrary::GetInstance().GetShader("ShadowMap");
    shader->Bind();

    shader->SetUniformMat4("u_LightView", m_MainLight.GetComponent<MCEngine::TransformComponent>().GetViewMatrix());
    shader->SetUniformMat4("u_LightProjection", glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, 1.0f, 20.0f));
    auto &&meshView = m_Registry.view<MCEngine::TransformComponent, MCEngine::MeshRendererComponent>();
    for (auto &&entity : meshView)
    {
        auto &&[transform, mesh] = meshView.get<MCEngine::TransformComponent, MCEngine::MeshRendererComponent>(entity);
        shader->SetUniformMat4("u_Model", transform.GetTransformMatrix());
        mesh.GetVAO()->Render(MCEngine::RendererType::Triangles);
    }

    shader->Unbind();
    m_ShadowMap->Unbind();
}

void MCEngine::Scene::Render(const Entity &camera) const
{
    ENGINE_PROFILE_FUNCTION();

    if (!camera || !camera.HasComponent<CameraComponent>() || !camera.HasComponent<TransformComponent>())
        return;

    UniformBufferLibrary::GetInstance().UpdateUniformBuffer(
        "UniformBuffer0",
        {
            {glm::value_ptr(camera.GetComponent<TransformComponent>().GetViewMatrix()), sizeof(glm::mat4), 0},
            {glm::value_ptr(camera.GetComponent<CameraComponent>().GetProjectionMatrix()), sizeof(glm::mat4),
             sizeof(glm::mat4)},
            {glm::value_ptr(camera.GetComponent<TransformComponent>().GetPosition()), sizeof(glm::vec3),
             sizeof(glm::mat4) + sizeof(glm::mat4)},
        });

    Render2D();
    Render3D();
    RenderSkybox();
}

void MCEngine::Scene::RenderColorID(const Entity &camera) const
{
    ENGINE_PROFILE_FUNCTION();

    if (!camera || !camera.HasComponent<CameraComponent>() || !camera.HasComponent<TransformComponent>())
        return;

    auto &&shader = MCEngine::ShaderLibrary::GetInstance().GetShader("ColorIDPicking");
    shader->Bind();

    // Pick 2D
    auto &&spriteView = m_Registry.view<MCEngine::TransformComponent, MCEngine::SpriteRendererComponent>();
    for (auto &&entity : spriteView)
    {
        auto &&[transform, sprite] =
            spriteView.get<MCEngine::TransformComponent, MCEngine::SpriteRendererComponent>(entity);
        shader->SetUniformMat4("u_Model", transform.GetTransformMatrix());
        shader->SetUniformUInt("u_EntityID", static_cast<unsigned int>(entity) + 1); // 0 = no entity
        sprite.GetVAO()->Render();
    }

    // Pick 3D
    auto &&meshView = m_Registry.view<MCEngine::TransformComponent, MCEngine::MeshRendererComponent>();
    for (auto &&entity : meshView)
    {
        auto &&[transform, mesh] = meshView.get<MCEngine::TransformComponent, MCEngine::MeshRendererComponent>(entity);
        shader->SetUniformMat4("u_Model", transform.GetTransformMatrix());
        shader->SetUniformUInt("u_EntityID", static_cast<unsigned int>(entity) + 1); // 0 = no entity
        mesh.GetVAO()->Render(MCEngine::RendererType::Triangles);
    }

    shader->Unbind();
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

void MCEngine::Scene::DeleteEntity(const Entity &entity)
{
    ENGINE_PROFILE_FUNCTION();

    if (!entity || !entity.GetRegistry().valid(entity.GetHandle()))
        return;

    // Remove from parent's children list and Recursively delete children
    if (entity.HasComponent<RelationshipComponent>())
    {
        auto &&relationship = entity.GetComponent<RelationshipComponent>();
        if (relationship.GetParent() && relationship.GetParent().HasComponent<RelationshipComponent>())
        {
            auto &&parentRelationship = relationship.GetParent().GetComponent<RelationshipComponent>();
            parentRelationship.RemoveChild(entity);
        }
        for (auto &&child : relationship.GetChildren())
        {
            DeleteEntity(child);
        }
    }

    // Call OnDestroy for NativeScriptComponent
    if (entity.HasComponent<NativeScriptComponent>())
    {
        entity.GetComponent<NativeScriptComponent>().DestroyScript();
    }

    m_Registry.destroy(entity.GetHandle());
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

MCEngine::Entity MCEngine::Scene::Add2DObject(const std::string &name, const TransformComponent &transform,
                                              const SpriteRendererComponent &spriteRenderer)
{
    Entity entity = AddEmptyEntity(name, transform);
    entity.AddComponent<SpriteRendererComponent>(spriteRenderer);
    return entity;
}

MCEngine::Entity MCEngine::Scene::Add3DObject(const std::string &name, const TransformComponent &transform,
                                              const MeshRendererComponent &meshRenderer)
{
    Entity entity = AddEmptyEntity(name, transform);
    entity.AddComponent<MeshRendererComponent>(meshRenderer);
    return entity;
}

MCEngine::Entity MCEngine::Scene::AddCamera(const std::string &name, const TransformComponent &transform,
                                            const CameraComponent &cameraComponent)
{
    Entity entity = AddEmptyEntity(name, transform);
    entity.AddComponent<CameraComponent>(cameraComponent);
    return entity;
}

MCEngine::Entity MCEngine::Scene::AddLight(const std::string &name, const TransformComponent &transform,
                                           const LightComponent &lightComponent)
{
    Entity entity = AddEmptyEntity(name, transform);
    entity.AddComponent<LightComponent>(lightComponent);
    return entity;
}

void MCEngine::Scene::Render2D() const
{
    ENGINE_PROFILE_FUNCTION();

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
        sprite.GetTexture()->Bind(0);
        sprite.GetVAO()->Render();
    }

    shader->Unbind();
}

void MCEngine::Scene::Render3D() const
{
    ENGINE_PROFILE_FUNCTION();

    auto &&meshView = m_Registry.view<MCEngine::TransformComponent, MCEngine::MeshRendererComponent>();
    for (auto &&entity : meshView)
    {
        auto &&[transform, mesh] = meshView.get<MCEngine::TransformComponent, MCEngine::MeshRendererComponent>(entity);
        auto &&shader = mesh.GetShader();
        shader->Bind();

        // Shadow
        if (m_MainLight)
        {
            shader->SetUniformInt("u_ShadowMap", 0);
            m_ShadowMap->GetTexture()->Bind(0);
            shader->SetUniformMat4("u_LightView",
                                   m_MainLight.GetComponent<MCEngine::TransformComponent>().GetViewMatrix());
            shader->SetUniformMat4("u_LightProjection", glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, 1.0f, 20.0f));
        }

        // Light
        auto &&lightView = m_Registry.view<MCEngine::TransformComponent, MCEngine::LightComponent>();
        for (auto &&entity : lightView)
        {
            auto &&[transform, light] = lightView.get<MCEngine::TransformComponent, MCEngine::LightComponent>(entity);

            if (light.GetType() == MCEngine::LightType::Directional)
            {
                MCEngine::UniformBufferLibrary::GetInstance().UpdateUniformBuffer(
                    "UniformBuffer0",
                    {{glm::value_ptr(glm::normalize(-transform.GetPosition())), sizeof(glm::vec3),
                      sizeof(glm::mat4) + sizeof(glm::mat4) + sizeof(glm::vec4)},
                     {glm::value_ptr(light.GetColor() * light.GetIntensity()), sizeof(glm::vec3),
                      sizeof(glm::mat4) + sizeof(glm::mat4) + sizeof(glm::vec4) + sizeof(glm::vec4)}});
            }
            else if (light.GetType() == MCEngine::LightType::Point)
            {
                shader->SetUniformVec3("u_PointLight.Position", transform.GetPosition());
                shader->SetUniformVec3("u_PointLight.Color", light.GetColor() * light.GetIntensity());
                shader->SetUniformFloat("u_PointLight.Constant", light.GetConstant());
                shader->SetUniformFloat("u_PointLight.Linear", light.GetLinear());
                shader->SetUniformFloat("u_PointLight.Quadratic", light.GetQuadratic());
            }
            else if (light.GetType() == MCEngine::LightType::Spot)
            {
                shader->SetUniformVec3("u_SpotLight.Position", transform.GetPosition());
                shader->SetUniformVec3("u_SpotLight.Direction", -transform.GetUp());
                shader->SetUniformVec3("u_SpotLight.Color", light.GetColor() * light.GetIntensity());
                shader->SetUniformFloat("u_SpotLight.Constant", light.GetConstant());
                shader->SetUniformFloat("u_SpotLight.Linear", light.GetLinear());
                shader->SetUniformFloat("u_SpotLight.Quadratic", light.GetQuadratic());
                shader->SetUniformFloat("u_SpotLight.CutOff", glm::cos(glm::radians(light.GetInnerAngle())));
                shader->SetUniformFloat("u_SpotLight.OuterCutOff", glm::cos(glm::radians(light.GetOuterAngle())));
            }
        }

        auto &&offsets = mesh.GetOffsets();
        if (offsets.empty())
        {
            shader->SetUniformMat4("u_Model", transform.GetTransformMatrix());
        }
        else
        {
            // Instance
            for (int instanceCount = 0; instanceCount < offsets.size(); instanceCount++)
            {
                shader->SetUniformMat4("u_Models[" + std::to_string(instanceCount) + "]",
                                       offsets[instanceCount] * transform.GetTransformMatrix());
            }
        }

        mesh.GetMaterial().Bind(shader, "u_Material");
        mesh.GetVAO()->Render();
        shader->Unbind();
    }
}

void MCEngine::Scene::RenderSkybox() const
{
    ENGINE_PROFILE_FUNCTION();

    MCEngine::RendererCommand::DisableDepthTest();
    auto &&shader = MCEngine::ShaderLibrary::GetInstance().GetShader("Skybox");
    shader->Bind();

    auto &&view = m_Registry.view<MCEngine::SkyboxComponent>();
    if (!view.empty())
    {
        if (view.size() > 1)
            LOG_ENGINE_WARN("Multiple SkyboxComponents detected! Only the first one will be rendered.");

        auto &&skybox = m_Registry.get<MCEngine::SkyboxComponent>(view.front());
        shader->SetUniformInt("u_Skybox", 0);
        skybox.GetTextureCube()->Bind(0);
        MCEngine::VAOLibrary::GetInstance().GetVAO("Skybox")->Render();
    }

    shader->Unbind();
    MCEngine::RendererCommand::EnableDepthTest();
}
