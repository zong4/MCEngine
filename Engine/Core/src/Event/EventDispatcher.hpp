#pragma once

#include "Event.hpp"

namespace MCEngine
{

class EventDispatcher
{
public:
    EventDispatcher(Event &eventRef) : m_EventRef(eventRef) {}

    template <typename T> bool Dispatch(const std::function<bool(T &)> &func)
    {
        if (T *ev = dynamic_cast<T *>(&m_EventRef))
        {
            bool result = func(*ev);
            m_EventRef.SetHandled(result);

            // result ? LOG_ENGINE_TRACE("Event dispatched: " + m_Event.ToString())
            //        : LOG_ENGINE_WARN("Event not handled: " + m_Event.ToString());
            return result;
        }
        return false;
    }

private:
    Event &m_EventRef;
};

} // namespace MCEngine