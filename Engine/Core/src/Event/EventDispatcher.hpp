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
            bool result = func(*ev);
            m_Event.SetHandled(result);
            return result;
        }
        return false;
    }

private:
    Event &m_Event;
};

} // namespace MCEngine