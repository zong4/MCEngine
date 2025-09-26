#include "Math.hpp"

glm::mat4 MCEngine::Math::CreateTransformationMatrix(const glm::vec3 &translation, const glm::vec3 &rotation,
                                                     const glm::vec3 &scale)
{
    ENGINE_PROFILE_FUNCTION();

    glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f), translation);

    glm::mat4 rotationX = glm::rotate(glm::mat4(1.0f), glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
    glm::mat4 rotationY = glm::rotate(glm::mat4(1.0f), glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
    glm::mat4 rotationZ = glm::rotate(glm::mat4(1.0f), glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
    glm::mat4 rotationMatrix = rotationZ * rotationY * rotationX;

    glm::mat4 scaleMatrix = glm::scale(glm::mat4(1.0f), scale);

    return translationMatrix * rotationMatrix * scaleMatrix;
}