#pragma once

#include <Function.hpp>

namespace MCEditor
{

class EmptyScene : public MCEngine::Scene
{
public:
    EmptyScene();
    virtual ~EmptyScene() = default;
};

} // namespace MCEditor