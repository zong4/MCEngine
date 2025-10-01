#pragma once

#include "pch.hpp"

namespace MCEngine
{

class Material
{
public:
    Material(const glm::vec4 &color, float ambient, float diffuse, float specular, float shininess);

    // Getters
    glm::vec4 &GetColor() { return m_Color; }
    float &GetAmbientStrength() { return m_AmbientStrength; }
    float &GetDiffuseStrength() { return m_DiffuseStrength; }
    float &GetSpecularStrength() { return m_SpecularStrength; }
    float &GetShininess() { return m_Shininess; }
    const glm::vec4 &GetColor() const { return m_Color; }
    const float &GetAmbientStrength() const { return m_AmbientStrength; }
    const float &GetDiffuseStrength() const { return m_DiffuseStrength; }
    const float &GetSpecularStrength() const { return m_SpecularStrength; }
    float GetShininess() const { return m_Shininess; }

    // Setters
    void SetColor(const glm::vec4 &color) { m_Color = color; }
    void SetAmbientStrength(float ambient) { m_AmbientStrength = ambient; }
    void SetDiffuseStrength(float diffuse) { m_DiffuseStrength = diffuse; }
    void SetSpecularStrength(float specular) { m_SpecularStrength = specular; }
    void SetShininess(float shininess) { m_Shininess = shininess; }

public:
    void Bind(const std::shared_ptr<Shader> &shader, const std::string &name) const;

    std::string ToString() const;

private:
    glm::vec4 m_Color;
    float m_AmbientStrength;
    float m_DiffuseStrength;
    float m_SpecularStrength;
    float m_Shininess;
};

} // namespace MCEngine
