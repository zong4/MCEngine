#pragma once

#include <Function.hpp>

namespace MCEditor
{

class Editor : public MCEngine::Application
{
public:
    Editor()
    {
        std::cout << "Editor created." << std::endl;
    }
    ~Editor() final
    {
        std::cout << "Editor destroyed." << std::endl;
    }
};

} // namespace MCEditor