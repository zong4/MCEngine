#pragma once

#include "Event.hpp"

namespace MCEngine
{

class KeyEvent : public Event
{
public:
    KeyEvent(int keycode, int action) : m_KeyCode(keycode), m_Action(action) {}

    inline int GetKeyCode() const { return m_KeyCode; }
    inline int GetAction() const { return m_Action; }

    std::string ToString() const override
    {
        std::stringstream ss;
        ss << "KeyEvent: " << m_KeyCode << ", " << m_Action;
        return ss.str();
    }

protected:
    int m_KeyCode;
    int m_Action;
};

} // namespace MCEngine