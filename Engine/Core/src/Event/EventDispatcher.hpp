#pragma once

#include "Event.hpp"

namespace MCEngine
{

class EventDispatcher
{
public:
    EventDispatcher(Event &event) : m_Event(event) {}

    template <typename T> bool Dispatch(const std::function<bool(T &)> &func)
    {
        if (T *ev = dynamic_cast<T *>(&m_Event))
        {
            bool result = func(*ev);
            m_Event.SetHandled(result);
            // result ? LOG_ENGINE_TRACE("Event dispatched: " + m_Event.ToString())
            //        : LOG_ENGINE_WARN("Event not handled: " + m_Event.ToString());
            return result;
        }
        return false;
    }

private:
    Event &m_Event;
};

} // namespace MCEngine