#pragma once

#include <Function.hpp>

namespace MCEditor
{

class Editor : public MCEngine::Application
{
public:
    Editor() { LOG_EDITOR_INFO("Editor created."); }
    ~Editor() final { LOG_EDITOR_INFO("Editor destroyed."); }
};

} // namespace MCEditor