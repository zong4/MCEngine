#include "VAOLibrary.hpp"

#include <glad/glad.h>

namespace MCEngine
{

struct IdentitySquareData
{
    float vertices[20] = {
        0.5f,  0.5f,  0.0f, 1.0, 1.0, // top right
        0.5f,  -0.5f, 0.0f, 1.0, 0.0, // bottom right
        -0.5f, -0.5f, 0.0f, 0.0, 0.0, // bottom left
        -0.5f, 0.5f,  0.0f, 0.0, 1.0, // top left
    };
    unsigned int indices[6] = {
        // note that we start from 0!
        0, 3, 1, // first Triangle
        1, 3, 2  // second Triangle
    };
};
inline const IdentitySquareData g_IdentitySquareData;

struct SkyboxCubeData
{
    float vertices[108] = {
        // clang-format off
        // positions          
        -1.0f,  1.0f, -1.0f,
        -1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,

        -1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,

         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,

        -1.0f, -1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,

        -1.0f,  1.0f, -1.0f,
         1.0f,  1.0f, -1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f, -1.0f,

        -1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f,  1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f,  1.0f,
         1.0f, -1.0f,  1.0f
        // clang-format on
    };
};
inline const SkyboxCubeData g_SkyboxCubeData;

} // namespace MCEngine

MCEngine::VAOLibrary &MCEngine::VAOLibrary::GetInstance()
{
    static VAOLibrary instance;
    return instance;
}

std::string MCEngine::VAOLibrary::GetName(const std::shared_ptr<VertexArray> &vao) const
{
    for (const auto &[name, ptr] : m_VAOs)
    {
        if (ptr == vao)
            return name;
    }
    LOG_ENGINE_WARN("VAO not found in library");
    return "";
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
    LOG_ENGINE_TRACE("VAO added: " + name);
}

MCEngine::VAOLibrary::VAOLibrary()
{
    ENGINE_PROFILE_FUNCTION();

    static int MaxCubesNumber = 10000;

    auto &&cubesVAO = std::make_shared<VertexArray>(
        VertexBuffer(MaxCubesNumber * sizeof(CubeVertex) * 36),
        std::vector<VertexAttribute>{
            {0, 1, GL_UNSIGNED_INT, GL_FALSE, sizeof(CubeVertex), (const void *)(0 * sizeof(float))},
            {1, 3, GL_FLOAT, GL_FALSE, sizeof(CubeVertex), (const void *)(1 * sizeof(float))},
            {2, 3, GL_FLOAT, GL_FALSE, sizeof(CubeVertex), (const void *)(4 * sizeof(float))},
            {3, 4, GL_FLOAT, GL_FALSE, sizeof(CubeVertex), (const void *)(7 * sizeof(float))},
            {4, 4, GL_FLOAT, GL_FALSE, sizeof(CubeVertex), (const void *)(11 * sizeof(float))}});
    AddVAO("Cubes", cubesVAO);

    auto &&vertexArray = std::make_shared<VertexArray>(
        MCEngine::VertexBuffer(g_IdentitySquareData.vertices, sizeof(g_IdentitySquareData.vertices)),
        std::vector<VertexAttribute>{{0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (const void *)0},
                                     {1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (const void *)(3 * sizeof(float))}},
        MCEngine::IndexBuffer(g_IdentitySquareData.indices, sizeof(g_IdentitySquareData.indices)));
    AddVAO("Square", vertexArray);

    vertexArray = std::make_shared<VertexArray>(
        MCEngine::VertexBuffer(g_SkyboxCubeData.vertices, sizeof(g_SkyboxCubeData.vertices)),
        std::vector<VertexAttribute>{{0, 3, GL_FLOAT, GL_FALSE, 0, (const void *)0}});
    AddVAO("Skybox", vertexArray);

    LOG_ENGINE_INFO("VAO Library initialized");
}

bool MCEngine::VAOLibrary::Exists(const std::string &name) const { return m_VAOs.find(name) != m_VAOs.end(); }