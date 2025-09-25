#include "Object.hpp"

#include "Renderer/ShaderLibrary.hpp"

MCEngine::Object::Object(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale)
    : m_Position(position), m_Rotation(rotation), m_Scale(scale)
{
}

void MCEngine::Object::Render(const std::string &pipeline)
{
    if (m_VertexArray)
    {
        ShaderLibrary::GetInstance().Get(pipeline)->SetUniformMat4("u_Model", GetTransform());

        m_VertexArray->Bind();
        m_VertexArray->Render();
        m_VertexArray->Unbind();
    }
}

glm::mat4 MCEngine::Object::GetTransform() const
{
    glm::mat4 translation = glm::translate(glm::mat4(1.0f), glm::vec3(m_Position.x, m_Position.y, m_Position.z));

    glm::mat4 rotationX = glm::rotate(glm::mat4(1.0f), glm::radians(m_Rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
    glm::mat4 rotationY = glm::rotate(glm::mat4(1.0f), glm::radians(m_Rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
    glm::mat4 rotationZ = glm::rotate(glm::mat4(1.0f), glm::radians(m_Rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
    glm::mat4 rotation = rotationZ * rotationY * rotationX;

    glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(m_Scale.x, m_Scale.y, m_Scale.z));

    return translation * rotation * scale;
}