#pragma once

#include <Function.hpp>

namespace MCEditor
{

class HierarchyPanel
{
public:
    HierarchyPanel() = default;
    ~HierarchyPanel() = default;

public:
    void OnImGuiRender(std::shared_ptr<MCEngine::Scene> scene, MCEngine::Entity &selectedEntity);

private:
    void DrawEntityNode(MCEngine::Entity entity, MCEngine::Entity &selectedEntity);
};

} // namespace MCEditor