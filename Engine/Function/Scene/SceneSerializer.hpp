#pragma once

#include "Scene.hpp"

namespace YAML
{

// clang-format off
template <>
// clang-format on
struct convert<glm::vec3>
{
    static Node encode(const glm::vec3 &rhs)
    {
        Node node;
        node.push_back(rhs.x);
        node.push_back(rhs.y);
        node.push_back(rhs.z);
        return node;
    }
    static bool decode(const Node &node, glm::vec3 &rhs)
    {
        if (!node.IsSequence() || node.size() != 3)
            return false;

        rhs.x = node[0].as<float>();
        rhs.y = node[1].as<float>();
        rhs.z = node[2].as<float>();
        return true;
    }
};

// clang-format off
template <>
// clang-format on
struct convert<glm::vec4>
{
    static Node encode(const glm::vec4 &rhs)
    {
        Node node;
        node.push_back(rhs.x);
        node.push_back(rhs.y);
        node.push_back(rhs.z);
        node.push_back(rhs.w);
        return node;
    }
    static bool decode(const Node &node, glm::vec4 &rhs)
    {
        if (!node.IsSequence() || node.size() != 4)
            return false;

        rhs.x = node[0].as<float>();
        rhs.y = node[1].as<float>();
        rhs.z = node[2].as<float>();
        rhs.w = node[3].as<float>();
        return true;
    }
};

} // namespace YAML

namespace MCEngine
{

class SceneSerializer
{
public:
    SceneSerializer(std::shared_ptr<Scene> scene) : m_Scene(scene) {}
    ~SceneSerializer() = default;

    void Serialize(const std::string &filePath);
    bool Deserialize(const std::string &filePath);

private:
    std::shared_ptr<Scene> m_Scene;

private:
    Entity DeserializeEntity(YAML::Node &entity);
};

} // namespace MCEngine