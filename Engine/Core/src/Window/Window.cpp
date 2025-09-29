#include "Window.hpp"

#include "Event/EventDispatcher.hpp"
#include "Event/Key/KeyEvent.hpp"
#include "Event/MouseEvent.hpp"
#include "Event/WindowEvent.hpp"
#include "Renderer/RendererCommand.hpp"
#include <GLFW/glfw3.h>
#include <glad/glad.h>

MCEngine::WindowProps::WindowProps(const std::string &title, int width, int height, bool vsync,
                                   const glm::vec4 &backgroundColor)
    : m_Title(title), m_Width(width), m_Height(height), m_VSync(vsync), m_BackgroundColor(backgroundColor)
{
}

std::string MCEngine::WindowProps::ToString() const
{
    std::stringstream ss;
    ss << "WindowProps: " << m_Title << " (" << m_Width << ", " << m_Height
       << "), VSync: " << (m_VSync ? "true" : "false") << ", BackgroundColor: " + MCEngine::ToString(m_BackgroundColor);
    return ss.str();
}

MCEngine::Window::Window(const WindowProps &props) : m_Props(props) { Init(); }

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

void MCEngine::Window::Update(float deltaTime)
{
    ENGINE_PROFILE_FUNCTION();

    m_LayerStack.Update(deltaTime);

    glfwSwapBuffers(static_cast<GLFWwindow *>(m_NativeWindowPtr));
    glfwPollEvents();
}

void MCEngine::Window::Render(float deltaTime)
{
    ENGINE_PROFILE_FUNCTION();

    MCEngine::RendererCommand::SetClearColor(m_Props.GetBackgroundColor());
    MCEngine::RendererCommand::Clear();
    m_LayerStack.Render(deltaTime);
}

void MCEngine::Window::Init()
{
    ENGINE_PROFILE_FUNCTION();

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, 1);
#endif
    LOG_ENGINE_INFO("GLFW version: " + std::string(glfwGetVersionString()));

    // Enable 4x MSAA
    glfwWindowHint(GLFW_SAMPLES, 4);
    LOG_ENGINE_INFO("4x MSAA enabled");

    m_NativeWindowPtr =
        glfwCreateWindow(m_Props.GetWidth(), m_Props.GetHeight(), m_Props.GetTitle().c_str(), nullptr, nullptr);
    if (!m_NativeWindowPtr)
    {
        LOG_ENGINE_ERROR("Failed to create GLFW window");
        glfwTerminate();
    }
    LOG_ENGINE_INFO("GLFW window created: " + m_Props.ToString());

    glfwMakeContextCurrent(static_cast<GLFWwindow *>(m_NativeWindowPtr));
    SetCallbacks();
    SetVSync(m_Props.IsVSync());

    // Initialize GLAD
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    LOG_ENGINE_INFO("OpenGL version: " + std::string((const char *)glGetString(GL_VERSION)));

    RendererCommand::Init();
}

void MCEngine::Window::Shutdown()
{
    ENGINE_PROFILE_FUNCTION();

    glfwDestroyWindow(static_cast<GLFWwindow *>(m_NativeWindowPtr));
    glfwTerminate();

    LOG_ENGINE_INFO("Window destroyed.");
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
                                       win->GetProps().SetWidth(width);
                                       win->GetProps().SetHeight(height);
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

    m_Props.SetVSync(enabled);
    enabled ? glfwSwapInterval(1) : glfwSwapInterval(0);

    LOG_ENGINE_INFO("VSync " + std::string(enabled ? "enabled" : "disabled"));
}
