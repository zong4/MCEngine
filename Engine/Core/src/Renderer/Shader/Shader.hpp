#pragma once

#include "pch.hpp"

namespace MCEngine
{

class Shader
{
public:
    Shader(const std::string &vertexSource, const std::string &fragmentSource);
    virtual ~Shader();

    unsigned int GetRendererID() const { return m_RendererID; }

public:
    void Bind() const;
    void Unbind() const;

    void SetUniformMat4(const std::string &name, glm::mat4 matrix);

private:
    unsigned int m_RendererID = 0;

private:
    void CompileShader(unsigned int shaderID, const std::string &source);
    void LinkProgram(unsigned int programID);
};

} // namespace MCEngine
