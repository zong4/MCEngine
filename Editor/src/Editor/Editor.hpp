#pragma once

#include "EditorImGuiLayer.hpp"
#include "EditorLayer.hpp"

namespace MCEditor
{

class Editor : public MCEngine::Application
{
public:
    Editor(const MCEngine::WindowProps &props);
    ~Editor() final;
};

} // namespace MCEditor