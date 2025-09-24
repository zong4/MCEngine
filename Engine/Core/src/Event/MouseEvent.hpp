#pragma once

#include "Event.hpp"

namespace MCEngine
{

class MouseMoveEvent : public MCEngine::Event
{
public:
    MouseMoveEvent(float x, float y) : m_X(x), m_Y(y) {}

    inline float GetX() const { return m_X; }
    inline float GetY() const { return m_Y; }

    std::string ToString() const override
    {
        std::stringstream ss;
        ss << "MouseMoveEvent: " << m_X << ", " << m_Y;
        return ss.str();
    }

private:
    float m_X;
    float m_Y;
};

class MouseButtonEvent : public MCEngine::Event
{
public:
    MouseButtonEvent(int button, int action) : m_Button(button), m_Action(action) {}

    inline int GetButton() const { return m_Button; }
    inline int GetAction() const { return m_Action; }

    std::string ToString() const override
    {
        std::stringstream ss;
        ss << "MouseButtonEvent: " << m_Button << ", " << m_Action;
        return ss.str();
    }

private:
    int m_Button;
    int m_Action;
};

} // namespace MCEngine
