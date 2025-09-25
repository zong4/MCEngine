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

void MCEngine::Window::OnEvent(Event &e) { m_LayerStack->OnEvent(e); }

void MCEngine::Window::PreUpdate()
{
    glClearColor(m_Props.BackgroundColor[0], m_Props.BackgroundColor[1], m_Props.BackgroundColor[2],
                 m_Props.BackgroundColor[3]);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void MCEngine::Window::PostUpdate()
{
    glfwSwapBuffers(static_cast<GLFWwindow *>(m_NativeWindow));
    glfwPollEvents();
}

bool MCEngine::Window::ShouldClose() const { return glfwWindowShouldClose(static_cast<GLFWwindow *>(m_NativeWindow)); }

void MCEngine::Window::Init()
{
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    m_NativeWindow = glfwCreateWindow(m_Props.Width, m_Props.Height, m_Props.Title.c_str(), nullptr, nullptr);
    if (!m_NativeWindow)
    {
        LOG_ENGINE_ERROR("Failed to create GLFW window");
        glfwTerminate();
    }

    glfwMakeContextCurrent(static_cast<GLFWwindow *>(m_NativeWindow));
    SetCallbacks();
    SetVSync(m_Props.VSync);
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    glEnable(GL_DEPTH_TEST);

    m_LayerStack = std::make_unique<LayerStack>();

    LOG_ENGINE_INFO("Window initialized: " + m_Props.ToString());
}

void MCEngine::Window::SetCallbacks()
{
    glfwSetWindowUserPointer(static_cast<GLFWwindow *>(m_NativeWindow), this);

    glfwSetFramebufferSizeCallback(static_cast<GLFWwindow *>(m_NativeWindow),
                                   [](GLFWwindow *window, int width, int height) {
                                       glViewport(0, 0, width, height);

                                       glfwGetWindowSize(window, &width, &height);
                                       WindowResizeEvent event(width, height);

                                       Window *win = static_cast<Window *>(glfwGetWindowUserPointer(window));
                                       win->OnEvent(event);
                                   });

    glfwSetKeyCallback(static_cast<GLFWwindow *>(m_NativeWindow),
                       [](GLFWwindow *window, int key, int scancode, int action, int mods) {
                           KeyEvent event(key, action);

                           Window *win = static_cast<Window *>(glfwGetWindowUserPointer(window));
                           win->OnEvent(event);
                       });

    glfwSetMouseButtonCallback(static_cast<GLFWwindow *>(m_NativeWindow),
                               [](GLFWwindow *window, int button, int action, int mods) {
                                   MouseButtonEvent event(button, action);

                                   Window *win = static_cast<Window *>(glfwGetWindowUserPointer(window));
                                   win->OnEvent(event);
                               });

    glfwSetCursorPosCallback(static_cast<GLFWwindow *>(m_NativeWindow),
                             [](GLFWwindow *window, double xpos, double ypos) {
                                 MouseMoveEvent event(xpos, ypos);

                                 Window *win = static_cast<Window *>(glfwGetWindowUserPointer(window));
                                 win->OnEvent(event);
                             });
}

void MCEngine::Window::SetVSync(bool enabled)
{
    if (enabled)
    {
        glfwSwapInterval(1);
    }
    else
    {
        glfwSwapInterval(0);
    }
}

void MCEngine::Window::Shutdown()
{
    glfwDestroyWindow(static_cast<GLFWwindow *>(m_NativeWindow));
    glfwTerminate();
}