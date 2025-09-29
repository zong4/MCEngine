#include "Material.hpp"

MCEngine::Material::Material(const glm::vec4 &objectColor, const glm::vec3 &ambient, const glm::vec3 &diffuse,
                             const glm::vec3 &specular, float shininess)
    : m_ObjectColor(objectColor), m_AmbientStrength(ambient), m_DiffuseStrength(diffuse), m_SpecularStrength(specular),
      m_Shininess(shininess)
{
    LOG_ENGINE_INFO("Material created with " + ToString());
}

std::string MCEngine::Material::ToString() const
{
    return "Material(ObjectColor: " + MCEngine::ToString(m_ObjectColor) +
           ", Ambient: " + MCEngine::ToString(m_AmbientStrength) +
           ", Diffuse: " + MCEngine::ToString(m_DiffuseStrength) +
           ", Specular: " + MCEngine::ToString(m_SpecularStrength) + ", Shininess: " + std::to_string(m_Shininess) +
           ")";
}