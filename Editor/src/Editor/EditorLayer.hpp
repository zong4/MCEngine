#pragma once

#include <Function.hpp>

namespace MCEngine
{

class EditorLayer : public Layer
{

public:
    EditorLayer();
    virtual ~EditorLayer() = default;

    void OnAttach() override {}
    void OnDetach() override {}

public:
    void OnEvent(Event &event) override;
    void OnUpdate(float deltaTime) override;
    void OnRender() override;
    void OnImGuiRender(float deltaTime) override {}

private:
    std::shared_ptr<Scene> m_Scene;
};

} // namespace MCEngine