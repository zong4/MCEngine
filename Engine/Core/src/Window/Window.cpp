#include "Window.hpp"

#include "Event/EventDispatcher.hpp"
#include "Event/KeyEvent.hpp"
#include "Event/MouseEvent.hpp"
#include "Event/WindowEvent.hpp"
#include <GLFW/glfw3.h>
#include <glad/glad.h>

MCEngine::WindowProps::WindowProps(int width, int height, std::string title, bool vsync, float backgroundColor[4])
    : Width(width), Height(height), Title(title), VSync(vsync),
      BackgroundColor{backgroundColor[0], backgroundColor[1], backgroundColor[2], backgroundColor[3]}
{
}

std::string MCEngine::WindowProps::ToString() const
{
    std::stringstream ss;
    ss << "WindowProps: " << Title << " (" << Width << ", " << Height << "), VSync: " << (VSync ? "true" : "false")
       << ", BackgroundColor: (" << BackgroundColor[0] << ", " << BackgroundColor[1] << ", " << BackgroundColor[2]
       << ", " << BackgroundColor[3] << ")";
    return ss.str();
}

MCEngine::Window::Window(WindowProps props) : m_Props(props) { Init(); }

MCEngine::Window::~Window() { Shutdown(); }

bool MCEngine::Window::ShouldClose() const
{
    return glfwWindowShouldClose(static_cast<GLFWwindow *>(m_NativeWindowPtr)) || !m_Running;
}

void MCEngine::Window::OnEvent(Event &e)
{
    ENGINE_PROFILE_FUNCTION();

    m_LayerStack.OnEvent(e);
}

void MCEngine::Window::PreUpdate()
{
    ENGINE_PROFILE_FUNCTION();

    glClearColor(m_Props.BackgroundColor[0], m_Props.BackgroundColor[1], m_Props.BackgroundColor[2],
                 m_Props.BackgroundColor[3]);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void MCEngine::Window::Update(float deltaTime)
{
    ENGINE_PROFILE_FUNCTION();

    m_LayerStack.Update(deltaTime);
}

void MCEngine::Window::Render(float deltaTime)
{
    ENGINE_PROFILE_FUNCTION();

    m_LayerStack.Render(deltaTime);
}

void MCEngine::Window::PostUpdate()
{
    ENGINE_PROFILE_FUNCTION();

    glfwSwapBuffers(static_cast<GLFWwindow *>(m_NativeWindowPtr));
    glfwPollEvents();
}

void MCEngine::Window::Init()
{
    ENGINE_PROFILE_FUNCTION();

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    m_NativeWindowPtr = glfwCreateWindow(m_Props.Width, m_Props.Height, m_Props.Title.c_str(), nullptr, nullptr);
    if (!m_NativeWindowPtr)
    {
        LOG_ENGINE_ERROR("Failed to create GLFW window");
        glfwTerminate();
    }

    glfwMakeContextCurrent(static_cast<GLFWwindow *>(m_NativeWindowPtr));
    SetCallbacks();
    SetVSync(m_Props.VSync);
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    glEnable(GL_DEPTH_TEST);

    LOG_ENGINE_INFO("Window created: " + m_Props.ToString());
}

void MCEngine::Window::SetCallbacks()
{
    ENGINE_PROFILE_FUNCTION();

    glfwSetWindowUserPointer(static_cast<GLFWwindow *>(m_NativeWindowPtr), this);

    glfwSetFramebufferSizeCallback(static_cast<GLFWwindow *>(m_NativeWindowPtr),
                                   [](GLFWwindow *window, int width, int height) {
                                       glViewport(0, 0, width, height);

                                       glfwGetWindowSize(window, &width, &height);
                                       WindowResizeEvent event(width, height);

                                       Window *win = static_cast<Window *>(glfwGetWindowUserPointer(window));
                                       win->OnEvent(event);
                                   });

    glfwSetKeyCallback(static_cast<GLFWwindow *>(m_NativeWindowPtr),
                       [](GLFWwindow *window, int key, int scancode, int action, int mods) {
                           KeyEvent event(key, action);

                           Window *win = static_cast<Window *>(glfwGetWindowUserPointer(window));
                           win->OnEvent(event);
                       });

    glfwSetMouseButtonCallback(static_cast<GLFWwindow *>(m_NativeWindowPtr),
                               [](GLFWwindow *window, int button, int action, int mods) {
                                   MouseButtonEvent event(button, action);

                                   Window *win = static_cast<Window *>(glfwGetWindowUserPointer(window));
                                   win->OnEvent(event);
                               });

    glfwSetCursorPosCallback(static_cast<GLFWwindow *>(m_NativeWindowPtr),
                             [](GLFWwindow *window, double xpos, double ypos) {
                                 MouseMoveEvent event(xpos, ypos);

                                 Window *win = static_cast<Window *>(glfwGetWindowUserPointer(window));
                                 win->OnEvent(event);
                             });
}

void MCEngine::Window::SetVSync(bool enabled)
{
    ENGINE_PROFILE_FUNCTION();

    m_Props.VSync = enabled;
    enabled ? glfwSwapInterval(1) : glfwSwapInterval(0);

    LOG_ENGINE_TRACE("VSync " + std::string(enabled ? "enabled" : "disabled"));
}

void MCEngine::Window::Shutdown()
{
    ENGINE_PROFILE_FUNCTION();

    glfwDestroyWindow(static_cast<GLFWwindow *>(m_NativeWindowPtr));
    glfwTerminate();

    LOG_ENGINE_INFO("Window destroyed.");
}