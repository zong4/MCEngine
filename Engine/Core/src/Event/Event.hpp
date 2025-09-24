#pragma once

namespace MCEngine
{

class Event
{
public:
    Event() = default;
    virtual ~Event() = default;

    bool IsHandled() const { return Handled; }
    void SetHandled(bool handled) { Handled = handled; }

    virtual std::string ToString() const = 0;

protected:
    bool Handled = false;
};

} // namespace MCEngine