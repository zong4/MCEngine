#pragma once

#include "pch.hpp"

namespace MCEngine
{

class WindowProperty
{
public:
    WindowProperty(const std::string &title, int width, int height, bool vsync, const glm::vec4 &backgroundColor);

    // Getters
    const std::string &GetTitle() const { return m_Title; }
    int GetWidth() const { return m_Width; }
    int GetHeight() const { return m_Height; }
    bool IsVSync() const { return m_VSync; }
    const glm::vec4 &GetBackgroundColor() const { return m_BackgroundColor; }

    // Setters
    void SetWidth(int width) { m_Width = width; }
    void SetHeight(int height) { m_Height = height; }
    void SetVSync(bool vsync) { m_VSync = vsync; }

public:
    std::string ToString() const;

private:
    std::string m_Title;
    int m_Width;
    int m_Height;
    bool m_VSync;
    glm::vec4 m_BackgroundColor;
};

} // namespace MCEngine
