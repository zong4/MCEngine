#pragma once

#include "pch.hpp"

namespace MCEngine
{

struct TransformComponent
{
    glm::vec3 Position;
    glm::vec3 Rotation;
    glm::vec3 Scale;

public:
    TransformComponent() : Position(0.0f, 0.0f, 0.0f), Rotation(0.0f, 0.0f, 0.0f), Scale(1.0f, 1.0f, 1.0f) {}

    glm::mat4 GetTransformMatrix() const { return Math::CreateTransformationMatrix(Position, Rotation, Scale); }
};

struct SpriteRendererComponent
{
    glm::vec4 Color;

    SpriteRendererComponent() : Color(1.0f, 1.0f, 1.0f, 1.0f) {}
};

} // namespace MCEngine