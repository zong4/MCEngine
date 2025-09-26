#pragma once

#include "pch.hpp"

namespace MCEngine
{

class Math
{
public:
    static float ToRadians(float degrees) { return degrees * (3.14159265359f / 180.0f); }
    static float ToDegrees(float radians) { return radians * (180.0f / 3.14159265359f); }

    static glm::mat4 CreateTransformationMatrix(const glm::vec3 &translation, const glm::vec3 &rotation,
                                                const glm::vec3 &scale);
};

} // namespace MCEngine