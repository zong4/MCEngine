#pragma once

#include <Function.hpp>

namespace MCEditor
{

class HierarchyPanel
{
public:
    HierarchyPanel() = default;
    ~HierarchyPanel() = default;

    MCEngine::Entity GetSelectedEntity() const { return m_SelectedEntity; }

public:
    void OnImGuiRender(std::shared_ptr<MCEngine::Scene> scene);

private:
    MCEngine::Entity m_SelectedEntity;

private:
    void DrawEntityNode(MCEngine::Entity entity);
};

} // namespace MCEditor