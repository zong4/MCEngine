#pragma once

#include "pch.hpp"

namespace MCEngine
{

class MouseLibrary
{
public:
    static MouseLibrary &GetInstance();

    // Getters
    bool IsButtonDown(int button) const;
    bool IsButtonPressed(int button) const;
    bool IsButtonReleased(int button) const;
    const std::pair<double, double> &GetPosition() const { return m_Position; }
    const std::pair<double, double> &GetLastPosition() const { return m_LastPosition; }
    std::pair<double, double> GetDeltaPosition() const
    {
        return {m_Position.first - m_LastPosition.first, m_Position.second - m_LastPosition.second};
    }
    const std::pair<double, double> &GetScrollOffset() const { return m_ScrollOffset; }

    // Setters
    void SetButtonState(int button, int action) { m_ButtonStates[button] = action; }
    void SetPosition(double x, double y)
    {
        m_LastPosition = m_Position;
        m_Position = {x, y};
    }
    void SetScrollOffset(double xOffset, double yOffset) { m_ScrollOffset = {xOffset, yOffset}; }

private:
    std::unordered_map<int, int> m_ButtonStates;
    std::pair<double, double> m_Position = {0.0, 0.0};
    std::pair<double, double> m_LastPosition = {0.0, 0.0};
    std::pair<double, double> m_ScrollOffset = {0.0, 0.0};

private:
    MouseLibrary() = default;
    ~MouseLibrary() = default;
};

} // namespace MCEngine