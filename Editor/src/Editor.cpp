#include "Application.hpp"
#include "EntryPoint.hpp"

class Editor : public Application
{
public:
    Editor()
    {
        std::cout << "Editor created." << std::endl;
    }
    ~Editor() override
    {
        std::cout << "Editor destroyed." << std::endl;
    }
};

std::unique_ptr<Application> CreateApplication()
{
    return std::make_unique<Editor>();
}
