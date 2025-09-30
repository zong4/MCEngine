#include "RendererCommand.hpp"

#include <glad/glad.h>

void MCEngine::RendererCommand::Init()
{
    ENGINE_PROFILE_FUNCTION();

    EnableDepthTest();
    EnableBlend();
    EnableFaceCulling();
    EnableMultisampling();
    glEnable(GL_FRAMEBUFFER_SRGB);

    LOG_ENGINE_INFO("RendererCommand initialized");
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
    LOG_ENGINE_TRACE("Blend enabled");
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

    int samples = 0;
    glGetIntegerv(GL_SAMPLES, &samples);
    LOG_ENGINE_INFO("MSAA samples = " + std::to_string(samples));

    glEnable(GL_MULTISAMPLE);
}

void MCEngine::RendererCommand::DisableMultisampling()
{
    ENGINE_PROFILE_FUNCTION();

    glDisable(GL_MULTISAMPLE);
    LOG_ENGINE_TRACE("Multi-sampling disabled");
}