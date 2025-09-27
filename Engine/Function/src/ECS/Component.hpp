#pragma once

#include "Camera/Camera.hpp"

namespace MCEngine
{

struct TransformComponent
{
    glm::vec3 Position;
    glm::vec3 Rotation;
    glm::vec3 Scale;

public:
    TransformComponent(glm::vec3 position = glm::vec3(0.0f), glm::vec3 rotation = glm::vec3(0.0f),
                       glm::vec3 scale = glm::vec3(1.0f));

    glm::mat4 GetTransformMatrix() const;
};

struct SpriteRendererComponent
{
    std::shared_ptr<VertexArray> VAOPtr;
    glm::vec4 Color;

public:
    SpriteRendererComponent(std::shared_ptr<VertexArray> vao, glm::vec4 color = glm::vec4(1.0f));
};

struct MeshRendererComponent
{
    std::shared_ptr<VertexArray> VAOPtr;
    glm::vec4 Color;

public:
    MeshRendererComponent(std::shared_ptr<VertexArray> vao, glm::vec4 color = glm::vec4(1.0f));
};

struct CameraComponent
{
    std::shared_ptr<Camera> CameraPtr;

public:
    CameraComponent(std::shared_ptr<Camera> camera);
};

} // namespace MCEngine