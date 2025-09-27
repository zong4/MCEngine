#pragma once

#include "ECS/Component/Component.hpp"

namespace MCEngine
{

struct TransformComponent : public Component
{
    glm::vec3 Position;
    glm::vec3 Rotation;
    glm::vec3 Scale;

public:
    TransformComponent(glm::vec3 position = glm::vec3(0.0f), glm::vec3 rotation = glm::vec3(0.0f),
                       glm::vec3 scale = glm::vec3(1.0f))
        : Position(position), Rotation(rotation), Scale(scale)
    {
    }

    glm::mat4 GetTransformMatrix() const;
};

} // namespace MCEngine