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

class VAOLibrary
{
public:
    static VAOLibrary &GetInstance();

    std::shared_ptr<VertexArray> GetVAO(const std::string &name);
    void AddVAO(const std::string &name, const std::shared_ptr<VertexArray> &vao); // Add or replace

private:
    std::unordered_map<std::string, std::shared_ptr<VertexArray>> m_VAOs;

private:
    VAOLibrary();
    ~VAOLibrary() = default;

    bool Exists(const std::string &name) const;
};

} // namespace MCEngine