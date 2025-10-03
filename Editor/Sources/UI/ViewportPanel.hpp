#pragma once

#include <Function.hpp>

namespace MCEditor
{

class ViewportPanel
{

public:
    ViewportPanel(MCEngine::Entity camera);
    ~ViewportPanel() = default;

    // Getters
    bool IsFocused() const { return m_Focused; }

public:
    void Render(std::shared_ptr<MCEngine::Scene> scene);
    void OnImGuiRender();

private:
    bool m_Focused = false;
    bool m_ViewportDirty = false;
    glm::vec2 m_ViewportSize = {0.0f, 0.0f};
    MCEngine::Entity m_Camera;
    std::unique_ptr<MCEngine::FrameBuffer> m_FBOPtr;
    std::unique_ptr<MCEngine::FrameBuffer> m_MultisampleFBOPtr;
};

} // namespace MCEditor