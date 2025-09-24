#include "Window.hpp"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

MCEngine::Window::Window(int width, int height, std::string title) { Init(width, height, title); }

MCEngine::Window::~Window() { Shutdown(); }

void MCEngine::Window::SetVSync(bool enabled)
{
    m_VSync = enabled;

    if (m_VSync)
    {
        glfwSwapInterval(1);
    }
    else
    {
        glfwSwapInterval(0);
    }
}

void MCEngine::Window::PreUpdate()
{
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void MCEngine::Window::Update() {}

void MCEngine::Window::PostUpdate()
{
    glfwSwapBuffers(static_cast<GLFWwindow *>(m_Window));
    glfwPollEvents();
}

void MCEngine::Window::OnEvent(Event &e)
{
    EventDispatcher dispatcher(e);
    dispatcher.Dispatch<KeyEvent>([](KeyEvent &event) { LOG_ENGINE_TRACE(event.ToString()); });
    dispatcher.Dispatch<MouseMoveEvent>([](MouseMoveEvent &event) { LOG_ENGINE_TRACE(event.ToString()); });
    dispatcher.Dispatch<MouseButtonEvent>([](MouseButtonEvent &event) { LOG_ENGINE_TRACE(event.ToString()); });
}

bool MCEngine::Window::ShouldClose() const { return glfwWindowShouldClose(static_cast<GLFWwindow *>(m_Window)); }

void MCEngine::Window::Init(int width, int height, std::string title)
{
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    m_Window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
    if (!m_Window)
    {
        LOG_ENGINE_ERROR("Failed to create GLFW window");
        glfwTerminate();
    }

    glfwMakeContextCurrent(static_cast<GLFWwindow *>(m_Window));
    SetCallbacks();

    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

    glEnable(GL_DEPTH_TEST);

    SetVSync(true);

    LOG_ENGINE_INFO("Window initialized: " + title + " (" + std::to_string(width) + "x" + std::to_string(height) + ")");
}

void MCEngine::Window::Shutdown()
{
    glfwDestroyWindow(static_cast<GLFWwindow *>(m_Window));
    glfwTerminate();
}

void MCEngine::Window::SetCallbacks()
{
    glfwSetFramebufferSizeCallback(static_cast<GLFWwindow *>(m_Window),
                                   [](GLFWwindow *window, int width, int height) { glViewport(0, 0, width, height); });

    glfwSetWindowUserPointer(static_cast<GLFWwindow *>(m_Window), this);

    glfwSetKeyCallback(static_cast<GLFWwindow *>(m_Window),
                       [](GLFWwindow *window, int key, int scancode, int action, int mods) {
                           Window *win = static_cast<Window *>(glfwGetWindowUserPointer(window));
                           KeyEvent event(key, action);
                           win->OnEvent(event);
                       });

    glfwSetMouseButtonCallback(static_cast<GLFWwindow *>(m_Window),
                               [](GLFWwindow *window, int button, int action, int mods) {
                                   Window *win = static_cast<Window *>(glfwGetWindowUserPointer(window));
                                   MouseButtonEvent event(button, action);
                                   win->OnEvent(event);
                               });

    glfwSetCursorPosCallback(static_cast<GLFWwindow *>(m_Window), [](GLFWwindow *window, double xpos, double ypos) {
        Window *win = static_cast<Window *>(glfwGetWindowUserPointer(window));
        MouseMoveEvent event(xpos, ypos);
        win->OnEvent(event);
    });
}