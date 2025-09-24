#pragma once

#include "Event.hpp"

namespace MCEngine
{

class EventDispatcher
{
public:
    EventDispatcher(Event &e) : m_Event(e) {}

    template <typename T, typename F> bool Dispatch(const F &func)
    {
        if (T *ev = dynamic_cast<T *>(&m_Event))
        {
            func(*ev);
            m_Event.SetHandled(true);
            return true;
        }
        return false;
    }

private:
    Event &m_Event;
};

} // namespace MCEngine