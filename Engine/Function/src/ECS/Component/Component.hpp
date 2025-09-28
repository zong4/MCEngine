#pragma once

#include "pch.hpp"

namespace MCEngine
{

class Component
{
public:
    Component() = default;
    virtual ~Component() = default;

protected:
    bool m_Dirty = false;
};

} // namespace MCEngine