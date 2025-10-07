#pragma once

#include "Event.hpp"

namespace MCEngine
{

class MouseMoveEvent : public MCEngine::Event
{
public:
    MouseMoveEvent(double x, double y) : m_X(x), m_Y(y) {}

    double GetX() const { return m_X; }
    double GetY() const { return m_Y; }

public:
    std::string ToString() const override
    {
        std::stringstream ss;
        ss << "MouseMoveEvent: " << m_X << ", " << m_Y;
        return ss.str();
    }

private:
    double m_X;
    double m_Y;
};

class MouseButtonEvent : public MCEngine::Event
{
public:
    MouseButtonEvent(int button, int action) : m_Button(button), m_Action(action) {}

    int GetButton() const { return m_Button; }
    int GetAction() const { return m_Action; }

public:
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

class MouseScrollEvent : public MCEngine::Event
{
public:
    MouseScrollEvent(double xOffset, double yOffset) : m_XOffset(xOffset), m_YOffset(yOffset) {}

    double GetXOffset() const { return m_XOffset; }
    double GetYOffset() const { return m_YOffset; }

public:
    std::string ToString() const override
    {
        std::stringstream ss;
        ss << "MouseScrollEvent: " << m_XOffset << ", " << m_YOffset;
        return ss.str();
    }

private:
    double m_XOffset;
    double m_YOffset;
};

} // namespace MCEngine
