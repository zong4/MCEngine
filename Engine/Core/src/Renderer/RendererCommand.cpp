#include "RendererCommand.hpp"

#include <glad/glad.h>

void MCEngine::RendererCommand::Init()
{
    ENGINE_PROFILE_FUNCTION();

    EnableDepthTest();
    EnableBlend();
    EnableFaceCulling();
    EnableMultisampling();

    LOG_ENGINE_INFO("RendererCommand initialized.");
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
    LOG_ENGINE_INFO("Depth test enabled");
}

void MCEngine::RendererCommand::DisableDepthTest()
{
    ENGINE_PROFILE_FUNCTION();

    glDisable(GL_DEPTH_TEST);
    LOG_ENGINE_INFO("Depth test disabled");
}

void MCEngine::RendererCommand::EnableBlend()
{
    ENGINE_PROFILE_FUNCTION();

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    LOG_ENGINE_INFO("Blend enabled");
}

void MCEngine::RendererCommand::DisableBlend()
{
    ENGINE_PROFILE_FUNCTION();

    glDisable(GL_BLEND);
    LOG_ENGINE_INFO("Blend disabled");
}

void MCEngine::RendererCommand::EnableFaceCulling()
{
    ENGINE_PROFILE_FUNCTION();

    glEnable(GL_CULL_FACE);
    LOG_ENGINE_INFO("Face culling enabled");
}

void MCEngine::RendererCommand::DisableFaceCulling()
{
    ENGINE_PROFILE_FUNCTION();

    glDisable(GL_CULL_FACE);
    LOG_ENGINE_INFO("Face culling disabled");
}

void MCEngine::RendererCommand::EnableMultisampling()
{
    ENGINE_PROFILE_FUNCTION();

    // Enable multi-sampling
    int maxSamples = 0;
    glGetIntegerv(GL_MAX_SAMPLES, &maxSamples);
    LOG_ENGINE_INFO("Max samples supported: " + std::to_string(maxSamples));
    glEnable(GL_MULTISAMPLE);
}

void MCEngine::RendererCommand::DisableMultisampling()
{
    ENGINE_PROFILE_FUNCTION();

    glDisable(GL_MULTISAMPLE);
    LOG_ENGINE_INFO("Multi-sampling disabled");
}