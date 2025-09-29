#pragma once

#include "pch.hpp"

namespace MCEngine
{

class Material
{
public:
    Material(const glm::vec4 &objectColor, float ambient, float diffuse, float specular, float shininess);

    glm::vec4 &GetObjectColor() { return m_ObjectColor; }
    const glm::vec4 &GetObjectColor() const { return m_ObjectColor; }
    float &GetAmbientStrength() { return m_AmbientStrength; }
    const float &GetAmbientStrength() const { return m_AmbientStrength; }
    float &GetDiffuseStrength() { return m_DiffuseStrength; }
    const float &GetDiffuseStrength() const { return m_DiffuseStrength; }
    float &GetSpecularStrength() { return m_SpecularStrength; }
    const float &GetSpecularStrength() const { return m_SpecularStrength; }
    float &GetShininess() { return m_Shininess; }
    float GetShininess() const { return m_Shininess; }

    void SetObjectColor(const glm::vec4 &objectColor) { m_ObjectColor = objectColor; }
    void SetAmbientStrength(float ambient) { m_AmbientStrength = ambient; }
    void SetDiffuseStrength(float diffuse) { m_DiffuseStrength = diffuse; }
    void SetSpecularStrength(float specular) { m_SpecularStrength = specular; }
    void SetShininess(float shininess) { m_Shininess = shininess; }

public:
    std::string ToString() const;

private:
    glm::vec4 m_ObjectColor;
    float m_AmbientStrength;
    float m_DiffuseStrength;
    float m_SpecularStrength;
    float m_Shininess;
};

} // namespace MCEngine
