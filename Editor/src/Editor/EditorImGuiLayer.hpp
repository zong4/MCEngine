#pragma once

#include <Function.hpp>

namespace MCEngine
{

class EditorImGuiLayer : public ImGuiLayer
{
public:
    EditorImGuiLayer(std::shared_ptr<Window> windowPtr);
    ~EditorImGuiLayer() = default;

public:
    void OnUpdate(float deltaTime) override {}
    void OnRender() override {}

protected:
    void Begin(float deltaTime) override;

private:
    void BeginDockSpace();
    void RenderMenuBar();
    void EndDockSpace();
};

} // namespace MCEngine