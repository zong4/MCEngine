#pragma once

#include <glm/glm.hpp>
#include <string>

namespace MCEngine
{

static std::string ToString(const glm::vec3 &vec, int precision = 2)
{
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(precision);
    oss << "{" << vec.x << ", " << vec.y << ", " << vec.z << "}";
    return oss.str();
}

static std::string ToString(const glm::vec4 &vec, int precision = 2)
{
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(precision);
    oss << "{" << vec.x << ", " << vec.y << ", " << vec.z << ", " << vec.w << "}";
    return oss.str();
}

} // namespace MCEngine