#pragma once

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