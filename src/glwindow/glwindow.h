#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>

class GLWindow {
    public:

    GLWindow();

    GLWindow(GLint window_width, GLint window_height);

    ~GLWindow();

    int initialize();

    GLfloat getBufferWidth() const {
        return m_buffer_width;
    }  

    GLfloat getBufferHeight() const {
        return m_buffer_height;
    }

    bool shouldClose() const {
        return glfwWindowShouldClose(m_main_window);
    }

    void swapBuffers() {
        glfwSwapBuffers(m_main_window);
    }

    std::vector<bool>& getKeys() {
        return m_keys;
    }

    double getXChange();

    double getYChange();

    private:

    GLFWwindow* m_main_window;
    GLint m_buffer_width;
    GLint m_buffer_height;
    GLint m_window_width;
    GLint m_window_height;

    std::vector<bool> m_keys;

    double m_last_x_pos;
    double m_last_y_pos;
    bool m_first_time_pos_changed = true;
    double m_x_change = 0;
    double m_y_change = 0;

    void registerCallbacks();

    static void handleKeys(GLFWwindow* window, int key, int scancode, int action, int mods);
    static void handleMouse(GLFWwindow* window, double xpos, double ypos);
};