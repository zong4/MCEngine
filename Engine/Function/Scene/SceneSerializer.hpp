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
    SceneSerializer() = default;
    ~SceneSerializer() = default;

    static void Serialize(const std::shared_ptr<Scene> &scene, const std::string &filePath);
    static bool Deserialize(const std::shared_ptr<Scene> scene, const std::string &filePath);

private:
    static void SerializeEntity(YAML::Emitter &out, MCEngine::Entity entity);
    static Entity DeserializeEntity(std::shared_ptr<Scene> scene, YAML::Node &entity);
};

} // namespace MCEngine