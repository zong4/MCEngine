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

entt::entity MCEngine::EntityFactory::CreateBasicSquare(entt::registry &registry, const std::string &name,
                                                        const glm::vec3 &position, const glm::vec3 &rotation,
                                                        const glm::vec3 &scale)
{
    entt::entity entity = CreateEmptyEntity(registry, name, position, rotation, scale);
    AddComponents(registry, entity,
                  SpriteRendererComponent(MCEngine::VAOLibrary::GetInstance().GetVAO("IdentitySquare"),
                                          glm::vec4(1.0f, 0.7f, 0.8f, 1.0f),
                                          MCEngine::TextureLibrary::GetInstance().GetTexture("02BG")));
    LOG_ENGINE_TRACE("Basic Square Entity created with ID: " + std::to_string((uint32_t)entity));
    return entity;
}

entt::entity MCEngine::EntityFactory::CreateBasicCube(entt::registry &registry, const std::string &name,
                                                      const glm::vec3 &position, const glm::vec3 &rotation,
                                                      const glm::vec3 &scale)
{
    entt::entity entity = CreateEmptyEntity(registry, name, position, rotation, scale);
    AddComponents(registry, entity,
                  MeshRendererComponent(MCEngine::VAOLibrary::GetInstance().GetVAO("IdentityCube"),
                                        glm::vec4(0.0f, 0.0f, 1.0f, 0.8f)));
    LOG_ENGINE_TRACE("Basic Cube Entity created with ID: " + std::to_string((uint32_t)entity));
    return entity;
}

entt::entity MCEngine::EntityFactory::CreateBasicOrthoCamera(entt::registry &registry, const std::string &name,
                                                             const glm::vec3 &position, const glm::vec3 &rotation,
                                                             const glm::vec3 &size)
{
    entt::entity entity = CreateEmptyEntity(registry, name, position, rotation, glm::vec3(1.0f));
    AddComponents(registry, entity, OrthoCameraComponent(&registry.get<TransformComponent>(entity), size));
    LOG_ENGINE_TRACE("Basic Orthographic Camera Entity created with ID: " + std::to_string((uint32_t)entity));
    return entity;
}

entt::entity MCEngine::EntityFactory::CreateBasicPerspectiveCamera(entt::registry &registry, const std::string &name,
                                                                   const glm::vec3 &position, const glm::vec3 &rotation,
                                                                   float fov, float aspectRatio, float nearClip,
                                                                   float farClip)
{
    entt::entity entity = CreateEmptyEntity(registry, name, position, rotation, glm::vec3(1.0f));
    AddComponents(
        registry, entity,
        PerspectiveCameraComponent(&registry.get<TransformComponent>(entity), fov, aspectRatio, nearClip, farClip));
    LOG_ENGINE_TRACE("Basic Perspective Camera Entity created with ID: " + std::to_string((uint32_t)entity));
    return entity;
}