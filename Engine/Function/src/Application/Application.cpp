#include "Application.hpp"

#include "Window/Window.hpp"

void Application::Run()
{
    m_Window = std::make_unique<Window>(800, 600, "MC Engine");
    while (!m_Window->ShouldClose())
    {
        m_Window->Update();
    }
}