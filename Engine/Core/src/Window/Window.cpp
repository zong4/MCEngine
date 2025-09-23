#include "Window.hpp"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

MCEngine::Window::Window(int width, int height, std::string title)
{
    Init(width, height, title);
}

MCEngine::Window::~Window()
{
    Shutdown();
}

void MCEngine::Window::PreUpdate()
{
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void MCEngine::Window::Update()
{
}

void MCEngine::Window::PostUpdate()
{
    glfwSwapBuffers(static_cast<GLFWwindow *>(m_Window));
    glfwPollEvents();
}

bool MCEngine::Window::ShouldClose() const
{
    return glfwWindowShouldClose(static_cast<GLFWwindow *>(m_Window));
}

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
        std::cerr << "Failed to create GLFW window." << std::endl;
        glfwTerminate();
    }

    glfwMakeContextCurrent(static_cast<GLFWwindow *>(m_Window));

    glfwSetFramebufferSizeCallback(static_cast<GLFWwindow *>(m_Window),
                                   [](GLFWwindow *window, int width, int height) { glViewport(0, 0, width, height); });

    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

    glEnable(GL_DEPTH_TEST);
}

void MCEngine::Window::Shutdown()
{
    glfwDestroyWindow(static_cast<GLFWwindow *>(m_Window));
    glfwTerminate();
}