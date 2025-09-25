#pragma once

#include <Function.hpp>

namespace MCEditor
{

class Editor : public MCEngine::Application
{
public:
    Editor(MCEngine::WindowProps props);
    ~Editor() final;
};

} // namespace MCEditor