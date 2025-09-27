#pragma once

#include "VertexArray.hpp"

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

class VAOLibrary
{
public:
    static VAOLibrary &GetInstanceRef();

    std::shared_ptr<VertexArray> GetVAO(const std::string &name);
    void AddVAO(const std::string &name, const std::shared_ptr<VertexArray> &vao);

private:
    std::unordered_map<std::string, std::shared_ptr<VertexArray>> m_VAOMap;

private:
    VAOLibrary();
    ~VAOLibrary() = default;

    bool Exists(const std::string &name) const;
};

} // namespace MCEngine