#pragma once

#include "Renderer/Material/Material.hpp"

namespace MCEngine
{

class Shader
{
public:
    Shader(const std::string &vertexSource, const std::string &fragmentSource);
    ~Shader();

    unsigned int GetRendererID() const { return m_RendererID; }

    void SetUniformInt(const std::string &name, int value);
    void SetUniformFloat(const std::string &name, float value);
    void SetUniformVec3(const std::string &name, glm::vec3 vector3);
    void SetUniformVec4(const std::string &name, glm::vec4 vector4);
    void SetUniformMat4(const std::string &name, glm::mat4 matrix4);
    void SetUniformMaterial(const std::string &name, const Material &material);

public:
    void Bind() const;
    void Unbind() const;

private:
    unsigned int m_RendererID = 0;

private:
    void CompileShader(unsigned int shaderID, const std::string &source);
    void LinkProgram(unsigned int programID);
};

} // namespace MCEngine
