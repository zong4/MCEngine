#include "Component.hpp"

MCEngine::TransformComponent::TransformComponent(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale)
    : Position(position), Rotation(rotation), Scale(scale)
{
}

glm::mat4 MCEngine::TransformComponent::GetTransformMatrix() const
{
    ENGINE_PROFILE_FUNCTION();

    glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f), Position);

    glm::mat4 rotationX = glm::rotate(glm::mat4(1.0f), glm::radians(Rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
    glm::mat4 rotationY = glm::rotate(glm::mat4(1.0f), glm::radians(Rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
    glm::mat4 rotationZ = glm::rotate(glm::mat4(1.0f), glm::radians(Rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
    glm::mat4 rotationMatrix = rotationZ * rotationY * rotationX;

    glm::mat4 scaleMatrix = glm::scale(glm::mat4(1.0f), Scale);

    return translationMatrix * rotationMatrix * scaleMatrix;
}

MCEngine::SpriteRendererComponent::SpriteRendererComponent(std::shared_ptr<VertexArray> vaoPtr, glm::vec4 color)
    : VAOPtr(vaoPtr), Color(color)
{
}

MCEngine::MeshRendererComponent::MeshRendererComponent(std::shared_ptr<VertexArray> vaoPtr, glm::vec4 color)
    : VAOPtr(vaoPtr), Color(color)
{
}

MCEngine::CameraComponent::CameraComponent(std::shared_ptr<Camera> camera) : CameraPtr(camera) {}