#include "Shader.hpp"

#include <glad/glad.h>

MCEngine::Shader::Shader(const std::string &vertexSource, const std::string &fragmentSource)
{
    ENGINE_PROFILE_FUNCTION();

    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    CompileShader(vertexShader, vertexSource);

    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    CompileShader(fragmentShader, fragmentSource);

    m_RendererID = glCreateProgram();
    glAttachShader(m_RendererID, vertexShader);
    glAttachShader(m_RendererID, fragmentShader);
    LinkProgram(m_RendererID);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    LOG_ENGINE_INFO("Shader program created with ID: " + std::to_string(m_RendererID));
}

MCEngine::Shader::~Shader() { glDeleteProgram(m_RendererID); }

void MCEngine::Shader::Bind() const { glUseProgram(m_RendererID); }

void MCEngine::Shader::Unbind() const { glUseProgram(0); }

void MCEngine::Shader::SetUniformMat4(const std::string &name, glm::mat4 matrix)
{
    ENGINE_PROFILE_FUNCTION();

    int location = glGetUniformLocation(m_RendererID, name.c_str());
    glUniformMatrix4fv(location, 1, GL_FALSE, &matrix[0][0]);
}

void MCEngine::Shader::CompileShader(unsigned int shaderID, const std::string &source)
{
    ENGINE_PROFILE_FUNCTION();

    const char *sourceCStr = source.c_str();
    glShaderSource(shaderID, 1, &sourceCStr, nullptr);
    glCompileShader(shaderID);

    int success;
    char infoLog[512];
    glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(shaderID, 512, NULL, infoLog);
        LOG_ENGINE_ERROR("ERROR::SHADER::COMPILATION_FAILED\n" + std::string(infoLog));
    }
}

void MCEngine::Shader::LinkProgram(unsigned int programID)
{
    ENGINE_PROFILE_FUNCTION();

    glLinkProgram(programID);

    int success;
    char infoLog[512];
    glGetProgramiv(programID, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(programID, 512, NULL, infoLog);
        LOG_ENGINE_ERROR("ERROR::SHADER::PROGRAM::LINKING_FAILED\n" + std::string(infoLog));
    }
}
