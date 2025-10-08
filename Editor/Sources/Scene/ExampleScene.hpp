#pragma once

#include <Function.hpp>

namespace MCEditor
{

class ExampleScene : public MCEngine::Scene
{
public:
    ExampleScene();
    virtual ~ExampleScene() = default;

private:
    void WelcomeToMCEngine();
};

} // namespace MCEditor