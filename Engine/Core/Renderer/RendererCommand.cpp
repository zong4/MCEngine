#include "RendererCommand.hpp"

#include <glad/glad.h>

void MCEngine::RendererCommand::Init()
{
    ENGINE_PROFILE_FUNCTION();

    EnableDepthTest();
    EnableBlend();
    EnableFaceCulling();
    EnableMultisampling();
    EnableGammaCorrection();

    LOG_ENGINE_INFO("RendererCommand initialized");
}

void MCEngine::RendererCommand::GetError(const std::string &functionName)
{
    GLint error = glGetError();
    if (error != GL_NO_ERROR)
    {
        LOG_ENGINE_ERROR("OpenGL Error: " + std::to_string(error) + " in " + functionName);
    }
}

void MCEngine::RendererCommand::SetClearColor(const glm::vec4 &color)
{
    ENGINE_PROFILE_FUNCTION();

    glClearColor(color.r, color.g, color.b, color.a);
}

void MCEngine::RendererCommand::Clear()
{
    ENGINE_PROFILE_FUNCTION();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void MCEngine::RendererCommand::ClearColorBuffer()
{
    ENGINE_PROFILE_FUNCTION();

    glClear(GL_COLOR_BUFFER_BIT);
}

void MCEngine::RendererCommand::ClearDepthBuffer()
{
    ENGINE_PROFILE_FUNCTION();

    glClear(GL_DEPTH_BUFFER_BIT);
}

void MCEngine::RendererCommand::EnableDepthTest()
{
    ENGINE_PROFILE_FUNCTION();

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
}

void MCEngine::RendererCommand::DisableDepthTest()
{
    ENGINE_PROFILE_FUNCTION();

    glDepthFunc(GL_LEQUAL);
}

void MCEngine::RendererCommand::EnableBlend()
{
    ENGINE_PROFILE_FUNCTION();

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void MCEngine::RendererCommand::DisableBlend()
{
    ENGINE_PROFILE_FUNCTION();

    glDisable(GL_BLEND);
}

void MCEngine::RendererCommand::EnableFaceCulling()
{
    ENGINE_PROFILE_FUNCTION();

    glEnable(GL_CULL_FACE);
}

void MCEngine::RendererCommand::DisableFaceCulling()
{
    ENGINE_PROFILE_FUNCTION();

    glDisable(GL_CULL_FACE);
}

void MCEngine::RendererCommand::EnableMultisampling()
{
    ENGINE_PROFILE_FUNCTION();

    glEnable(GL_MULTISAMPLE);
}

void MCEngine::RendererCommand::DisableMultisampling()
{
    ENGINE_PROFILE_FUNCTION();

    glDisable(GL_MULTISAMPLE);
}

void MCEngine::RendererCommand::EnableGammaCorrection()
{
    ENGINE_PROFILE_FUNCTION();

    glEnable(GL_FRAMEBUFFER_SRGB);
}

void MCEngine::RendererCommand::DisableGammaCorrection()
{
    ENGINE_PROFILE_FUNCTION();

    glDisable(GL_FRAMEBUFFER_SRGB);
}