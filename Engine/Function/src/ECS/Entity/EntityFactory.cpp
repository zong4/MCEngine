#include "EntityFactory.hpp"

entt::entity MCEngine::EntityFactory::CreateEmptyEntity(entt::registry &registry, const std::string &name,
                                                        const glm::vec3 &position, const glm::vec3 &rotation,
                                                        const glm::vec3 &scale)
{
    entt::entity entity = registry.create();
    registry.emplace<TagComponent>(entity, name);
    registry.emplace<TransformComponent>(entity, position, rotation, scale);
    registry.emplace<RelationshipComponent>(entity);
    return entity;
}

entt::entity MCEngine::EntityFactory::CreateEmptyEntity(entt::registry &registry, const std::string &name,
                                                        const TransformComponent &transform)
{
    entt::entity entity = registry.create();
    registry.emplace<TagComponent>(entity, name);
    registry.emplace<TransformComponent>(entity, transform);
    registry.emplace<RelationshipComponent>(entity);
    return entity;
}

entt::entity MCEngine::EntityFactory::CreateSquare(entt::registry &registry, const std::string &name,
                                                   const glm::vec3 &position, const glm::vec3 &rotation,
                                                   const glm::vec3 &scale, const glm::vec4 &color,
                                                   std::shared_ptr<Texture> texturePtr)
{
    entt::entity entity = CreateEmptyEntity(registry, name, position, rotation, scale);
    AddComponents(
        registry, entity,
        SpriteRendererComponent(MCEngine::VAOLibrary::GetInstance().GetVAO("IdentitySquare"), color, texturePtr));
    LOG_ENGINE_TRACE("Basic Square Entity created with ID: " + std::to_string((uint32_t)entity));
    return entity;
}

entt::entity MCEngine::EntityFactory::CreateCube(entt::registry &registry, const std::string &name,
                                                 const glm::vec3 &position, const glm::vec3 &rotation,
                                                 const glm::vec3 &scale, const Material &material)
{
    entt::entity entity = CreateEmptyEntity(registry, name, position, rotation, scale);
    AddComponents(registry, entity,
                  MeshRendererComponent(MCEngine::VAOLibrary::GetInstance().GetVAO("IdentityCube"), material));
    LOG_ENGINE_TRACE("Basic Cube Entity created with ID: " + std::to_string((uint32_t)entity));
    return entity;
}

entt::entity MCEngine::EntityFactory::CreateOrthoCamera(entt::registry &registry, const std::string &name,
                                                        const glm::vec3 &position, const glm::vec3 &rotation,
                                                        const glm::vec3 &size)
{
    entt::entity entity = CreateEmptyEntity(registry, name, position, rotation, glm::vec3(1.0f));
    AddComponents(registry, entity, CameraComponent(&registry.get<TransformComponent>(entity), size));
    LOG_ENGINE_TRACE("Basic Orthographic Camera Entity created with ID: " + std::to_string((uint32_t)entity));
    return entity;
}

entt::entity MCEngine::EntityFactory::CreatePerspectiveCamera(entt::registry &registry, const std::string &name,
                                                              const glm::vec3 &position, const glm::vec3 &rotation,
                                                              float fov, float aspectRatio, float nearClip,
                                                              float farClip)
{
    entt::entity entity = CreateEmptyEntity(registry, name, position, rotation, glm::vec3(1.0f));
    AddComponents(registry, entity,
                  CameraComponent(&registry.get<TransformComponent>(entity), fov, aspectRatio, nearClip, farClip));
    LOG_ENGINE_TRACE("Basic Perspective Camera Entity created with ID: " + std::to_string((uint32_t)entity));
    return entity;
}

entt::entity MCEngine::EntityFactory::CreateDirectionalLight(entt::registry &registry, const std::string &name,
                                                             const glm::vec3 &position, const glm::vec3 &color,
                                                             float intensity)
{
    entt::entity entity = CreateEmptyEntity(registry, name, position);
    AddComponents(registry, entity, LightComponent(color, intensity));
    LOG_ENGINE_TRACE("Basic Directional Light Entity created with ID: " + std::to_string((uint32_t)entity));
    return entity;
}

entt::entity MCEngine::EntityFactory::CreatePointLight(entt::registry &registry, const std::string &name,
                                                       const glm::vec3 &position, const glm::vec3 &color,
                                                       float intensity, float constant, float linear, float quadratic)
{
    entt::entity entity = CreateEmptyEntity(registry, name, position);
    AddComponents(registry, entity, LightComponent(color, intensity, constant, linear, quadratic));
    LOG_ENGINE_TRACE("Basic Point Light Entity created with ID: " + std::to_string((uint32_t)entity));
    return entity;
}

entt::entity MCEngine::EntityFactory::CreateSpotLight(entt::registry &registry, const std::string &name,
                                                      const glm::vec3 &position, const glm::vec3 &color,
                                                      float intensity, float constant, float linear, float quadratic,
                                                      float cutOff, float outerCutOff)
{
    entt::entity entity = CreateEmptyEntity(registry, name, position);
    AddComponents(registry, entity, LightComponent(color, intensity, constant, linear, quadratic, cutOff, outerCutOff));
    LOG_ENGINE_TRACE("Basic Spot Light Entity created with ID: " + std::to_string((uint32_t)entity));
    return entity;
}