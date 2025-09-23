#pragma once

#include "pch.hpp"

namespace MCEngine
{

class Object
{
public:
    Object() = default;
    virtual ~Object() = default;

    virtual void Update() {}
    virtual void Render() {}
};

} // namespace MCEngine
