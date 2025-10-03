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
    Entity AddSquare(
        const std::string &name, const TransformComponent &transform = TransformComponent(),
        const glm::vec4 &color = glm::vec4(1.0f),
        const std::shared_ptr<Texture2D> &texturePtr = TextureLibrary::GetInstance().GetTexture2D("White"));
    Entity AddCube(const std::string &name, const TransformComponent &transform = TransformComponent(),
                   const std::shared_ptr<Shader> &shaderPtr = ShaderLibrary::GetInstance().GetShader("BlinnPhong"),
                   const Material &material = Material(glm::vec4(1.0f), 0.3f, 1.0f, 0.5f, 32.0f));
    Entity AddOrthoCamera(const std::string &name, const TransformComponent &transform = TransformComponent());
    Entity AddPerspectiveCamera(const std::string &name,
                                const TransformComponent &transform =
                                    TransformComponent(glm::vec3(0.0f, 5.0f, 8.0f), glm::vec3(-30.0f, 0.0f, 0.0f)));
    Entity AddDirectionalLight(const std::string &name,
                               const TransformComponent &transform = TransformComponent(glm::vec3(3.0f, 3.0f, 3.0f)),
                               const glm::vec3 &color = glm::vec3(1.0f, 0.0f, 0.0f), float intensity = 1.0f);
    Entity AddPointLight(const std::string &name,
                         const TransformComponent &transform = TransformComponent(glm::vec3(3.0f, 3.0f, 0.0f)),
                         const glm::vec3 &color = glm::vec3(1.0f), float intensity = 1.0f, float constant = 1.0f,
                         float linear = 0.09f, float quadratic = 0.032f);
    Entity AddSpotLight(const std::string &name,
                        const TransformComponent &transform = TransformComponent(glm::vec3(0.0f, 3.0f, 3.0f)),
                        const glm::vec3 &color = glm::vec3(1.0f), float intensity = 1.0f, float constant = 1.0f,
                        float linear = 0.09f, float quadratic = 0.032f, float cutOff = 12.5f,
                        float outerCutOff = 15.0f);

protected:
    Entity m_MainCamera;
    entt::registry m_Registry = {};
    std::unique_ptr<MCEngine::FrameBuffer> m_ShadowMapPtr =
        std::make_unique<MCEngine::FrameBuffer>(MCEngine::FrameBufferType::Depth, 2048, 2048);

protected:
    virtual void RenderShadowMapReally() const = 0;
    virtual void RenderReally() const = 0;
};

} // namespace MCEngine