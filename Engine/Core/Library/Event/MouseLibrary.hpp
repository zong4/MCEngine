#pragma once

namespace MCEngine
{

class MouseLibrary
{
public:
    static MouseLibrary &GetInstance();

    // Getters
    bool IsMouseButtonDown(int button) const;
    bool IsMouseButtonPressed(int button) const;
    bool IsMouseButtonReleased(int button) const;
    std::pair<double, double> GetMousePosition() const { return {m_MouseX, m_MouseY}; }
    double GetMouseX() const { return m_MouseX; }
    double GetMouseY() const { return m_MouseY; }
    double GetMouseDeltaX() const { return m_MouseDeltaX; }
    double GetMouseDeltaY() const { return m_MouseDeltaY; }

    // Setters
    void SetMouseButtonState(int button, int action);
    void SetMousePosition(double x, double y);
    void SetMouseScrollOffset(double xOffset, double yOffset)
    {
        m_MouseScrollXOffset = xOffset;
        m_MouseScrollYOffset = yOffset;
    }
    void EndFrame();

private:
    std::unordered_map<int, int> m_MouseButtonStateMap; // button, action
    double m_MouseX = 0.0;
    double m_MouseY = 0.0;
    double m_LastMouseX = 0.0;
    double m_LastMouseY = 0.0;

private:
    MouseLibrary();
    ~MouseLibrary() = default;
};

} // namespace MCEngine