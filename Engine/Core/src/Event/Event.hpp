#pragma once

#include <sstream>
#include <string>

namespace MCEngine
{

class Event
{
public:
    Event() = default;
    virtual ~Event() = default;

    bool IsHandled() const { return m_Handled; }
    void SetHandled(bool handled) { m_Handled = handled; }

    virtual std::string ToString() const = 0;

protected:
    bool m_Handled = false;
};

} // namespace MCEngine