#include "CameraComponent.hpp"

void MCEngine::CameraComponent::UpdateViewMatrix(glm::vec3 position, glm::vec3 rotation)
{
    glm::mat4 rotationX = glm::rotate(glm::mat4(1.0f), glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
    glm::mat4 rotationY = glm::rotate(glm::mat4(1.0f), glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
    glm::mat4 rotationZ = glm::rotate(glm::mat4(1.0f), glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
    glm::mat4 rotationXYZ = rotationZ * rotationY * rotationX;

    glm::vec3 front = glm::normalize(glm::vec3(rotationXYZ * glm::vec4(0.0f, 0.0f, -1.0f, 0.0f)));
    glm::vec3 up = glm::normalize(glm::vec3(rotationXYZ * glm::vec4(0.0f, 1.0f, 0.0f, 0.0f)));

    ViewMatrix = glm::lookAt(position, position + front, up);
}