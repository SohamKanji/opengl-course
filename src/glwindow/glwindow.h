#include <GL/glew.h>
#include <GLFW/glfw3.h>

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

    private:

    GLFWwindow* m_main_window;
    GLint m_buffer_width;
    GLint m_buffer_height;
    GLint m_window_width;
    GLint m_window_height;
};