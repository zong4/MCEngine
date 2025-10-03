#pragma once

#include "ECS/Entity/Entity.hpp"

#include "ECS/Component/Basic/BasicComponent.hpp"
#include "ECS/Component/Camera/CameraComponent.hpp"
#include "ECS/Component/Light/LightComponent.hpp"
#include "ECS/Component/Light/SkyboxComponent.hpp"
#include "ECS/Component/Renderer/RendererComponent.hpp"

namespace MCEngine
{

class Scene
{
public:
    Scene();
    virtual ~Scene();

    // Getters
    entt::registry &GetRegistry() { return m_Registry; }
    Entity GetMainCamera() const { return m_MainCamera; }

public:
    // Main loop
    void Update(float deltaTime);
    void RenderShadowMap() const;
    void Render(const Entity &camera) const;

    void Resize(float width, float height);

    Entity AddEmptyEntity(const std::string &name, const TransformComponent &transform = TransformComponent());
    Entity Add2DObject(const std::string &name, const TransformComponent &transform,
                       const SpriteRendererComponent &spriteRenderer =
                           SpriteRendererComponent(VAOLibrary::GetInstance().GetVAO("Square")));
    Entity Add3DObject(
        const std::string &name, const TransformComponent &transform,
        const MeshRendererComponent &meshRenderer = MeshRendererComponent(VAOLibrary::GetInstance().GetVAO("Cube")));
    Entity AddCamera(const std::string &name, const TransformComponent &transform,
                     const CameraComponent &cameraComponent);
    Entity AddLight(const std::string &name, const TransformComponent &transform, const LightComponent &lightComponent);

protected:
    Entity m_MainCamera;
    entt::registry m_Registry = {};
    std::unique_ptr<MCEngine::FrameBuffer> m_ShadowMapPtr =
        std::make_unique<MCEngine::FrameBuffer>(MCEngine::FrameBufferType::Depth, 2048, 2048);

protected:
    virtual void RenderShadowMapReally() const {}
    virtual void RenderReally() const {}
};

} // namespace MCEngine