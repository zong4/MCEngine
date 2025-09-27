#pragma once

#include "VertexArray.hpp"

namespace MCEngine
{

class VAOLibrary
{
public:
    static VAOLibrary &GetInstance();

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