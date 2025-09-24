#pragma once

#include "Event.hpp"
#include "Logger/Logger.hpp"

namespace MCEngine
{

class EventDispatcher
{
public:
    EventDispatcher(Event &e) : m_Event(e) {}

    template <typename T> bool Dispatch(const std::function<bool(T &)> &func)
    {
        if (T *ev = dynamic_cast<T *>(&m_Event))
        {
            bool result = func(*ev);
            m_Event.SetHandled(result);

            if (result == false)
            {
                LOG_ENGINE_WARN("Event not handled: " + m_Event.ToString());
            }
            else
            {
                LOG_ENGINE_TRACE("Event handled: " + m_Event.ToString());
            }

            return result;
        }
        return false;
    }

private:
    Event &m_Event;
};

} // namespace MCEngine