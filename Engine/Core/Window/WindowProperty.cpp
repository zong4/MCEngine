
#include "WindowProperty.hpp"

MCEngine::WindowProperty::WindowProperty(const std::string &title, int width, int height, bool vsync,
                                         const glm::vec4 &backgroundColor)
    : m_Title(title), m_Width(width), m_Height(height), m_VSync(vsync), m_BackgroundColor(backgroundColor)
{
}

std::string MCEngine::WindowProperty::ToString() const
{
    std::stringstream ss;
    ss << "WindowProperty: " << m_Title << " (" << m_Width << ", " << m_Height
       << "), VSync: " << (m_VSync ? "true" : "false") << ", BackgroundColor: " + MCEngine::ToString(m_BackgroundColor);
    return ss.str();
}