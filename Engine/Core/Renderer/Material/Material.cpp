#include "Material.hpp"

MCEngine::Material::Material(const glm::vec4 &objectColor, float ambient, float diffuse, float specular,
                             float shininess)
    : m_ObjectColor(objectColor), m_AmbientStrength(ambient), m_DiffuseStrength(diffuse), m_SpecularStrength(specular),
      m_Shininess(shininess)
{
    LOG_ENGINE_INFO("Material created with " + ToString());
}

std::string MCEngine::Material::ToString() const
{
    return "Material(ObjectColor: " + MCEngine::ToString(m_ObjectColor) +
           ", Ambient: " + std::to_string(m_AmbientStrength) + ", Diffuse: " + std::to_string(m_DiffuseStrength) +
           ", Specular: " + std::to_string(m_SpecularStrength) + ", Shininess: " + std::to_string(m_Shininess) + ")";
}