#include "Window.hpp"

#include "Event/EventDispatcher.hpp"
#include "Event/Key/KeyEvent.hpp"
#include "Event/MouseEvent.hpp"
#include "Event/WindowEvent.hpp"
#include "Renderer/RendererCommand.hpp"
#include <GLFW/glfw3.h>
#include <glad/glad.h>

MCEngine::Window::Window(const WindowProperty &property) : m_Property(property) { Init(); }

MCEngine::Window::~Window() { Shutdown(); }

bool MCEngine::Window::IsRunning() const
{
    ENGINE_PROFILE_FUNCTION();

    return glfwWindowShouldClose(static_cast<GLFWwindow *>(m_NativeWindowPtr)) || !m_Running;
}

void MCEngine::Window::SetVSync(bool enabled)
{
    ENGINE_PROFILE_FUNCTION();

    m_Property.SetVSync(enabled);
    enabled ? glfwSwapInterval(1) : glfwSwapInterval(0);
    LOG_ENGINE_INFO("VSync " + std::string(enabled ? "enabled" : "disabled"));
}

void MCEngine::Window::OnEvent(Event &e)
{
    ENGINE_PROFILE_FUNCTION();

    m_LayerStack.OnEvent(e);
}

void MCEngine::Window::Update(float deltaTime)
{
    ENGINE_PROFILE_FUNCTION();

    // Update
    m_LayerStack.Update(deltaTime);

    // Post-update
    glfwSwapBuffers(static_cast<GLFWwindow *>(m_NativeWindowPtr));
    glfwPollEvents();
}

void MCEngine::Window::Render(float deltaTime)
{
    ENGINE_PROFILE_FUNCTION();

    // Pre-render
    MCEngine::RendererCommand::SetClearColor(m_Property.GetBackgroundColor());
    MCEngine::RendererCommand::Clear();

    // Render
    m_LayerStack.Render(deltaTime);
}

void MCEngine::Window::Init()
{
    ENGINE_PROFILE_FUNCTION();

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, 1);
#endif
    LOG_ENGINE_INFO("GLFW version: " + std::string(glfwGetVersionString()));

    // Other window hints
    glfwWindowHint(GLFW_SAMPLES, 4);

    // Create window
    m_NativeWindowPtr = glfwCreateWindow(m_Property.GetWidth(), m_Property.GetHeight(), m_Property.GetTitle().c_str(),
                                         nullptr, nullptr);
    if (!m_NativeWindowPtr)
    {
        LOG_ENGINE_ERROR("Failed to create GLFW window");
        glfwTerminate();
    }
    LOG_ENGINE_INFO("GLFW window created: " + m_Property.ToString());

    // Make context current
    glfwMakeContextCurrent(static_cast<GLFWwindow *>(m_NativeWindowPtr));
    SetCallbacks();
    SetVSync(m_Property.IsVSync());

    // Initialize GLAD
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    LOG_ENGINE_INFO("OpenGL version: " + std::string((const char *)glGetString(GL_VERSION)));

    // Initialize Renderer
    RendererCommand::Init();
}

void MCEngine::Window::Shutdown()
{
    ENGINE_PROFILE_FUNCTION();

    glfwDestroyWindow(static_cast<GLFWwindow *>(m_NativeWindowPtr));
    glfwTerminate();
    LOG_ENGINE_INFO("Window destroyed");
}

void MCEngine::Window::SetCallbacks()
{
    ENGINE_PROFILE_FUNCTION();

    glfwSetWindowUserPointer(static_cast<GLFWwindow *>(m_NativeWindowPtr), this);

    glfwSetFramebufferSizeCallback(static_cast<GLFWwindow *>(m_NativeWindowPtr),
                                   [](GLFWwindow *nativeWindow, int width, int height) {
                                       // Framebuffer size
                                       glViewport(0, 0, width, height);

                                       // Window size
                                       glfwGetWindowSize(nativeWindow, &width, &height);

                                       // OnEvent
                                       Window *window = static_cast<Window *>(glfwGetWindowUserPointer(nativeWindow));
                                       window->GetProperty().SetWidth(width);
                                       window->GetProperty().SetHeight(height);

                                       // Notify event
                                       WindowResizeEvent event(width, height);
                                       window->OnEvent(event);
                                   });

    // todo: add mods
    glfwSetKeyCallback(static_cast<GLFWwindow *>(m_NativeWindowPtr),
                       [](GLFWwindow *nativeWindow, int key, int scancode, int action, int mods) {
                           Window *window = static_cast<Window *>(glfwGetWindowUserPointer(nativeWindow));
                           KeyEvent event(key, action);
                           window->OnEvent(event);
                       });

    // todo: add mods
    glfwSetMouseButtonCallback(static_cast<GLFWwindow *>(m_NativeWindowPtr),
                               [](GLFWwindow *nativeWindow, int button, int action, int mods) {
                                   Window *window = static_cast<Window *>(glfwGetWindowUserPointer(nativeWindow));
                                   MouseButtonEvent event(button, action);
                                   window->OnEvent(event);
                               });

    glfwSetCursorPosCallback(static_cast<GLFWwindow *>(m_NativeWindowPtr),
                             [](GLFWwindow *nativeWindow, double xPos, double yPos) {
                                 Window *window = static_cast<Window *>(glfwGetWindowUserPointer(nativeWindow));
                                 MouseMoveEvent event(xPos, yPos);
                                 window->OnEvent(event);
                             });
}
