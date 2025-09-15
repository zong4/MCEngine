#include "Window.hpp"

#include "Buffer/IndexBuffer.hpp"
#include "Buffer/VertexArray.hpp"
#include "Buffer/VertexBuffer.hpp"
#include "Shader/ShaderLibrary.hpp"
#include <GLFW/glfw3.h>
#include <glad/glad.h>

Window::Window(int width, int height, std::string title)
{
    Init(width, height, title);

    const char *vertexShaderSource = "#version 330 core\n"
                                     "layout (location = 0) in vec3 aPos;\n"
                                     "void main()\n"
                                     "{\n"
                                     "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
                                     "}\0";
    const char *fragmentShaderSource = "#version 330 core\n"
                                       "out vec4 FragColor;\n"
                                       "void main()\n"
                                       "{\n"
                                       "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
                                       "}\n\0";
    m_ShaderLibrary = std::make_unique<ShaderLibrary>();
    m_ShaderLibrary->Load("Standard", vertexShaderSource, fragmentShaderSource);

    float vertices[] = {
        0.5f,  0.5f,  0.0f, // top right
        0.5f,  -0.5f, 0.0f, // bottom right
        -0.5f, -0.5f, 0.0f, // bottom left
        -0.5f, 0.5f,  0.0f  // top left
    };
    unsigned int indices[] = {
        // note that we start from 0!
        0, 1, 3, // first Triangle
        1, 2, 3  // second Triangle
    };

    m_VertexArray = std::make_unique<VertexArray>();

    m_VertexArray->AddVertexBuffer(std::move(VertexBuffer(vertices, sizeof(vertices))));
    m_VertexArray->AddVertexAttribute({0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0});
    m_VertexArray->SetIndexBuffer(IndexBuffer(indices, sizeof(indices)));
}

Window::~Window()
{
    Shutdown();
}

void Window::Update()
{
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    m_ShaderLibrary->Get("Standard")->Bind();
    m_VertexArray->Bind();

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    m_VertexArray->Unbind();
    m_ShaderLibrary->Get("Standard")->Unbind();

    glfwSwapBuffers(static_cast<GLFWwindow *>(m_Window));
    glfwPollEvents();
}

bool Window::ShouldClose() const
{
    return glfwWindowShouldClose(static_cast<GLFWwindow *>(m_Window));
}

void Window::Init(int width, int height, std::string title)
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

void Window::Shutdown()
{
    glfwDestroyWindow(static_cast<GLFWwindow *>(m_Window));
    glfwTerminate();
}