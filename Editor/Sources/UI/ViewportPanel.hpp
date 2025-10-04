#pragma once

#include <Function.hpp>

namespace MCEditor
{

class ViewportPanel
{

public:
    ViewportPanel();
    ~ViewportPanel() = default;

    // Getters
    bool IsFocused() const { return m_Focused; }

public:
    void Render(MCEngine::Entity camera, std::shared_ptr<MCEngine::Scene> scene) const;
    void OnImGuiRender();

private:
    bool m_Focused = false;
    bool m_ViewportDirty = false;
    glm::vec2 m_ViewportSize = {0.0f, 0.0f};
    std::unique_ptr<MCEngine::FrameBuffer> m_FBOPtr;
    std::unique_ptr<MCEngine::FrameBuffer> m_MultisampleFBOPtr;
};

} // namespace MCEditor