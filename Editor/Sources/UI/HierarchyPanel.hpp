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
    void OnImGuiRender();

private:
    void DrawEntityNode(MCEngine::Entity entity);
};

} // namespace MCEditor