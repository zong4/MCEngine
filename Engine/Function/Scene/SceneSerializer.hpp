#pragma once

#include "Scene.hpp"

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
};

} // namespace MCEngine