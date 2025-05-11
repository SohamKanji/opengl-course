#include "glwindow.h"
#include <iostream>

GLWindow::GLWindow()
{
    m_main_window = nullptr;
    m_buffer_width = 0;
    m_buffer_height = 0;
    m_window_width = 800;
    m_window_height = 600;
}

GLWindow::GLWindow(GLint window_width, GLint window_height)
{
    m_main_window = nullptr;
    m_buffer_width = 0;
    m_buffer_height = 0;
    m_window_width = window_width;
    m_window_height = window_height;
}

GLWindow::~GLWindow()
{
    if(m_main_window != nullptr) {
        glfwDestroyWindow(m_main_window);
    }
    glfwTerminate();
}

int GLWindow::initialize()
{
    // Initialize GLFW
    if(!glfwInit())
    {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        glfwTerminate();
        return 1;
    }

    // Setup GLFW window properties
    // OpenGL version
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    // Core profile = No Backwards Compatibility
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    // Allow Forward Compatibility
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    m_main_window = glfwCreateWindow(m_window_width, m_window_height, "Test Window", nullptr, nullptr);
    if(m_main_window == nullptr) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return 1;
    }

    glfwGetFramebufferSize(m_main_window, &m_buffer_width, &m_buffer_height);

    // Set context for GLEW to use
    glfwMakeContextCurrent(m_main_window);

    // Allow modern extension features
    glewExperimental = GL_TRUE;

    if(glewInit() != GLEW_OK) 
    {
        std::cerr << "Failed to initialize GLEW" << std::endl;
        glfwDestroyWindow(m_main_window);
        glfwTerminate();
        return 1;
    }

    glEnable(GL_DEPTH_TEST); 

    // Setup Viewport size
    glViewport(0, 0, m_buffer_width, m_buffer_height);
}


