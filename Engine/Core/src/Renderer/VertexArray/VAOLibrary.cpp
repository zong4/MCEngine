#include "VAOLibrary.hpp"

#include <glad/glad.h>

MCEngine::VAOLibrary &MCEngine::VAOLibrary::GetInstance()
{
    static VAOLibrary instance;
    return instance;
}

std::shared_ptr<MCEngine::VertexArray> MCEngine::VAOLibrary::GetVAO(const std::string &name)
{
    ENGINE_PROFILE_FUNCTION();

    if (!Exists(name))
    {
        LOG_ENGINE_ERROR("VAO not found: " + name);
        return nullptr;
    }
    return m_VAOs[name];
}

void MCEngine::VAOLibrary::AddVAO(const std::string &name, const std::shared_ptr<VertexArray> &vao)
{
    ENGINE_PROFILE_FUNCTION();

    if (Exists(name))
    {
        LOG_ENGINE_WARN("VAO already exists: " + name);
        return;
    }
    m_VAOs[name] = vao;

    LOG_ENGINE_INFO("VAO added: " + name);
}

bool MCEngine::VAOLibrary::Exists(const std::string &name) const { return m_VAOs.find(name) != m_VAOs.end(); }

MCEngine::VAOLibrary::VAOLibrary()
{
    ENGINE_PROFILE_FUNCTION();

    auto vao = std::make_shared<VertexArray>(
        MCEngine::IndexBuffer(g_IdentitySquareData.indices,
                              sizeof(g_IdentitySquareData.indices) / sizeof(unsigned int)),
        MCEngine::VertexBuffer(g_IdentitySquareData.vertices, sizeof(g_IdentitySquareData.vertices)),
        MCEngine::VertexAttribute{0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (const void *)0});
    AddVAO("IdentitySquare", vao);

    LOG_ENGINE_INFO("VAO Library initialized.");
}