#pragma once

#include "pch.hpp"

namespace MCEngine
{

class Material
{
public:
    Material(const glm::vec4 &objectColor, const glm::vec3 &ambient, const glm::vec3 &diffuse,
             const glm::vec3 &specular, float shininess = 32.0f);

    glm::vec4 &GetObjectColor() { return m_ObjectColor; }
    const glm::vec4 &GetObjectColor() const { return m_ObjectColor; }
    glm::vec3 &GetAmbientStrength() { return m_AmbientStrength; }
    const glm::vec3 &GetAmbientStrength() const { return m_AmbientStrength; }
    glm::vec3 &GetDiffuseStrength() { return m_DiffuseStrength; }
    const glm::vec3 &GetDiffuseStrength() const { return m_DiffuseStrength; }
    glm::vec3 &GetSpecularStrength() { return m_SpecularStrength; }
    const glm::vec3 &GetSpecularStrength() const { return m_SpecularStrength; }
    float &GetShininess() { return m_Shininess; }
    float GetShininess() const { return m_Shininess; }

    void SetObjectColor(const glm::vec4 &objectColor) { m_ObjectColor = objectColor; }
    void SetAmbientStrength(const glm::vec3 &ambient) { m_AmbientStrength = ambient; }
    void SetDiffuseStrength(const glm::vec3 &diffuse) { m_DiffuseStrength = diffuse; }
    void SetSpecularStrength(const glm::vec3 &specular) { m_SpecularStrength = specular; }
    void SetShininess(float shininess) { m_Shininess = shininess; }

public:
    std::string ToString() const;

private:
    glm::vec4 m_ObjectColor;
    glm::vec3 m_AmbientStrength;
    glm::vec3 m_DiffuseStrength;
    glm::vec3 m_SpecularStrength;
    float m_Shininess;
};

} // namespace MCEngine
