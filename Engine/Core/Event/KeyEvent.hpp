#pragma once

#include "Event/Event.hpp"

namespace MCEngine
{

class KeyEvent : public Event
{
public:
    KeyEvent(int keycode, int action) : m_KeyCode(keycode), m_Action(action) {}

    int GetKeyCode() const { return m_KeyCode; }
    int GetAction() const { return m_Action; }

public:
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