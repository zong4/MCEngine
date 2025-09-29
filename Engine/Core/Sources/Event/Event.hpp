#pragma once

#include "pch.hpp"

namespace MCEngine
{

class Event
{
public:
    Event() = default;

    bool IsHandled() const { return m_Handled; }
    void SetHandled(bool handled) { m_Handled = handled; }

    virtual std::string ToString() const = 0;

protected:
    bool m_Handled = false;
};

} // namespace MCEngine