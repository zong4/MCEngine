#pragma once

#include "Event.hpp"

namespace MCEngine
{

class EventHandler
{
public:
    using EventCallbackFn = std::function<void(Event &)>;

    void SetCallback(EventCallbackFn callback) { m_Callback = callback; }

    void Handle(Event &e)
    {
        if (m_Callback)
        {
            m_Callback(e);
        }
    }

private:
    EventCallbackFn m_Callback;
};

} // namespace MCEngine