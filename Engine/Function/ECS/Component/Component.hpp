#pragma once

#include "pch.hpp"

namespace MCEngine
{

class Component
{
public:
    Component() = default;
    virtual ~Component() = default;

    virtual void Update(float deltaTime) = 0;
};

} // namespace MCEngine