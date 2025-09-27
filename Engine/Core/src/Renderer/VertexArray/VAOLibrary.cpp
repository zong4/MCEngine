#include "VAOLibrary.hpp"

#include <glad/glad.h>

namespace MCEngine
{

struct IdentitySquareData
{
    float vertices[12] = {
        0.5f,  0.5f,  0.0f, // top right
        0.5f,  -0.5f, 0.0f, // bottom right
        -0.5f, -0.5f, 0.0f, // bottom left
        -0.5f, 0.5f,  0.0f  // top left
    };
    unsigned int indices[6] = {
        // note that we start from 0!
        0, 1, 3, // first Triangle
        1, 2, 3  // second Triangle
    };
};
inline const IdentitySquareData g_IdentitySquareData;

struct IdentityCubeData
{
    float vertices[24] = {
        -0.5f, -0.5f, -0.5f, // 0
        0.5f,  -0.5f, -0.5f, // 1
        0.5f,  0.5f,  -0.5f, // 2
        -0.5f, 0.5f,  -0.5f, // 3
        -0.5f, -0.5f, 0.5f,  // 4
        0.5f,  -0.5f, 0.5f,  // 5
        0.5f,  0.5f,  0.5f,  // 6
        -0.5f, 0.5f,  0.5f   // 7
    };
    unsigned int indices[36] = {
        0, 1, 2, 2, 3, 0, // back face
        4, 5, 6, 6, 7, 4, // front face
        4, 5, 1, 1, 0, 4, // bottom face
        7, 6, 2, 2, 3, 7, // top face
        4, 0, 3, 3, 7, 4, // left face
        5, 1, 2, 2, 6, 5  // right face
    };
};
inline const IdentityCubeData g_IdentityCubeData;

struct IdentityCubeWithNormalsData
{
    float vertices[216] = {
        // clang-format off
        // positions          // normals
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f, // back face
         0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f, // front face
         0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,

        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f, // left face
        -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f, // right face
         0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f, // bottom face
         0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f, // top face
         0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
        // clang-format on
    };
};
inline const IdentityCubeWithNormalsData g_IdentityCubeWithNormalsData;

} // namespace MCEngine

MCEngine::VAOLibrary &MCEngine::VAOLibrary::GetInstanceRef()
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
    return m_VAOMap[name];
}

void MCEngine::VAOLibrary::AddVAO(const std::string &name, const std::shared_ptr<VertexArray> &vao)
{
    ENGINE_PROFILE_FUNCTION();

    if (Exists(name))
    {
        LOG_ENGINE_WARN("VAO already exists: " + name);
        return;
    }
    m_VAOMap[name] = vao;

    LOG_ENGINE_INFO("VAO added: " + name);
}

bool MCEngine::VAOLibrary::Exists(const std::string &name) const { return m_VAOMap.find(name) != m_VAOMap.end(); }

MCEngine::VAOLibrary::VAOLibrary()
{
    ENGINE_PROFILE_FUNCTION();

    auto vertexArray = std::make_shared<VertexArray>(
        MCEngine::VertexBuffer(g_IdentitySquareData.vertices, sizeof(g_IdentitySquareData.vertices)),
        std::vector<VertexAttribute>{{0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (const void *)0}},
        MCEngine::IndexBuffer(g_IdentitySquareData.indices, sizeof(g_IdentitySquareData.indices)));
    AddVAO("IdentitySquare", vertexArray);

    vertexArray = std::make_shared<VertexArray>(
        MCEngine::VertexBuffer(g_IdentityCubeData.vertices, sizeof(g_IdentityCubeData.vertices)),
        std::vector<VertexAttribute>{{0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (const void *)0}},
        MCEngine::IndexBuffer(g_IdentityCubeData.indices, sizeof(g_IdentityCubeData.indices)));
    AddVAO("IdentityCube", vertexArray);

    vertexArray = std::make_shared<VertexArray>(
        MCEngine::VertexBuffer(g_IdentityCubeWithNormalsData.vertices, sizeof(g_IdentityCubeWithNormalsData.vertices)),
        std::vector<VertexAttribute>{{0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (const void *)0},
                                     {1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (const void *)(3 * sizeof(float))}});
    AddVAO("IdentityCubeWithNormals", vertexArray);

    LOG_ENGINE_INFO("VAO Library initialized.");
}