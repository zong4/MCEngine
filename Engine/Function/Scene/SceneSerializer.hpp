#pragma once

#include "Scene.hpp"

namespace YAML
{
class Emitter;
class Node;
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