#pragma once

#include "pch.hpp"

class Shader
{
public:
    Shader(const std::string &vertexSource, const std::string &fragmentSource);
    virtual ~Shader();

    void Bind() const;
    void Unbind() const;

private:
    void CompileShader(unsigned int shaderID, const std::string &source);
    void LinkProgram(unsigned int programID);

private:
    unsigned int m_RendererID = 0;
};
