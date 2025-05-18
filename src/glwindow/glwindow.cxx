#include "glwindow.h"
#include <iostream>

GLWindow::GLWindow()
{
    m_main_window = nullptr;
    m_buffer_width = 0;
    m_buffer_height = 0;
    m_window_width = 800;
    m_window_height = 600;
    m_keys = std::vector<bool>(1024, false);
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

    registerCallbacks();
    glfwSetInputMode(m_main_window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

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

    glfwSetWindowUserPointer(m_main_window, this);

    // Setup Viewport size
    glViewport(0, 0, m_buffer_width, m_buffer_height);
}

void GLWindow::registerCallbacks()
{
    glfwSetKeyCallback(m_main_window, handleKeys);
    glfwSetCursorPosCallback(m_main_window, handleMouse);
}

void GLWindow::handleKeys(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    auto gl_window = static_cast<GLWindow*>(glfwGetWindowUserPointer(window));

    if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }

    if(key >= 0 && key < 1024) {
        if(action == GLFW_PRESS) {
            gl_window->m_keys[key] = true;
        } else if(action == GLFW_RELEASE) {
            gl_window->m_keys[key] = false;
        }
    }
}

void GLWindow::handleMouse(GLFWwindow* window, double xpos, double ypos)
{
    auto gl_window = static_cast<GLWindow*>(glfwGetWindowUserPointer(window));

    if(gl_window->m_first_time_pos_changed) {
        gl_window->m_last_x_pos = xpos;
        gl_window->m_last_y_pos = ypos;
        gl_window->m_first_time_pos_changed = false;
        return;
    }

    gl_window->m_x_change = xpos - gl_window->m_last_x_pos;
    gl_window->m_y_change = gl_window->m_last_y_pos - ypos;
    gl_window->m_last_x_pos = xpos;
    gl_window->m_last_y_pos = ypos;
}

double GLWindow::getXChange()
{
    double result = m_x_change;
    m_x_change = 0;
    return result;
}

double GLWindow::getYChange()
{
    double result = m_y_change;
    m_y_change = 0;
    return result;
}


