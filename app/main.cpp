#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

// Window Dimensions
const GLint WIDTH = 800;
const GLint HEIGHT = 600;
const static float TO_RADIANS = 3.14159265f / 180.0f;

GLuint vao, vbo, shader, uniform_model;

float x_offset = 0.0f;
float delta = 0.005f;
float max_offset = 0.7f;
float curr_angle = 0.0f;
float angle_delta = 0.5f;
float curr_size = 0.4f;
float max_size = 0.8f;
float min_size = 0.1f;
float size_delta = 0.01f;
bool direction = true;

static const char* VERTEX_SHADER = R"(
#version 330

layout(location = 0) in vec3 pos;

uniform mat4 model;

out vec4 v_color;

void main()
{
    gl_Position = model * vec4(pos, 1.0);
    v_color = vec4(clamp(pos, 0.0, 1.0), 1.0);
}
)";

static const char* FRAGMENT_SHADER = R"(
#version 330

in vec4 v_color;

out vec4 color;

void main()
{
    color = v_color;
}
)";

void createTriangle()
{
    GLfloat vertices[] = {
        -1.0f, -1.0f, 0.0f,
        1.0f, -1.0f, 0.0f,
        0.0f, 1.0f, 0.0f
    };

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void addShader(GLuint shader_program, const char* shader_code, GLenum shader_type)
{
    auto the_shader = glCreateShader(shader_type);

    const GLchar* the_code[1];
    the_code[0] = shader_code;

    GLint code_length[1];
    code_length[0] = strlen(shader_code);

    glShaderSource(the_shader, 1, the_code, code_length);
    glCompileShader(the_shader);

    GLint result = 0;
    GLchar eLog[1024] = {0};
    glGetShaderiv(the_shader, GL_COMPILE_STATUS, &result);
    if(!result) {
        glGetShaderInfoLog(the_shader, sizeof(eLog), nullptr, eLog);
        std::cerr << "Error compiling the " << shader_type << " shader: " << eLog << std::endl;
        return;
    }

    glAttachShader(shader_program, the_shader);
}

void compileShader()
{
    shader = glCreateProgram();

    if(!shader) {
        std::cerr << "Error creating shader program" << std::endl;
        return;
    }

    addShader(shader, VERTEX_SHADER, GL_VERTEX_SHADER);
    addShader(shader, FRAGMENT_SHADER, GL_FRAGMENT_SHADER);

    GLint result = 0;
    GLchar eLog[1024] = {0};

    glLinkProgram(shader);
    glGetProgramiv(shader, GL_LINK_STATUS, &result);

    if(!result) {
        glGetProgramInfoLog(shader, sizeof(eLog), nullptr, eLog);
        std::cerr << "Error linking program: " << eLog << std::endl;
        return;
    }

    glBindVertexArray(vao);
    glValidateProgram(shader);
    glGetProgramiv(shader, GL_VALIDATE_STATUS, &result);
    if(!result) {
        glGetProgramInfoLog(shader, sizeof(eLog), nullptr, eLog);
        std::cerr << "Error validating program: " << eLog << std::endl;
        return;
    }
    
    uniform_model = glGetUniformLocation(shader, "model");

    glBindVertexArray(0);
}


int main() 
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

    auto main_window = glfwCreateWindow(WIDTH, HEIGHT, "Test Window", nullptr, nullptr);
    if(main_window == nullptr) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return 1;
    }

    // Get Buffer size information
    int buffer_width, buffer_height;
    glfwGetFramebufferSize(main_window, &buffer_width, &buffer_height);

    // Set context for GLEW to use
    glfwMakeContextCurrent(main_window);

    // Allow modern extension features
    glewExperimental = GL_TRUE;

    if(glewInit() != GLEW_OK) 
    {
        std::cerr << "Failed to initialize GLEW" << std::endl;
        glfwDestroyWindow(main_window);
        glfwTerminate();
        return 1;
    }

    // Setup Viewport size
    glViewport(0, 0, buffer_width, buffer_height);

    createTriangle();
    compileShader();
    
    // Loop until window closed
    while(!glfwWindowShouldClose(main_window))
    {
        // Get + Handle user input events
        glfwPollEvents();

        if(direction) {
            x_offset += delta;
            curr_size += size_delta;
        } else {
            x_offset -= delta;
            curr_size -= size_delta;
        }

        if(abs(x_offset) >= max_offset) {
            direction = !direction;
        }

        curr_angle += angle_delta;
        if(curr_angle >= 360.0f) {
            curr_angle -= 360.0f;
        }

        // Clear window
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shader);

        glm::mat4 model(1.0f);
        // model = glm::translate(model, glm::vec3(x_offset, 0.0f, 0.0f));
        // model = glm::rotate(model, curr_angle * TO_RADIANS, glm::vec3(0.0f, 0.0f, 1.0f));
        model = glm::scale(model, glm::vec3(0.4f, 0.4f, 1.0f));
        glUniformMatrix4fv(uniform_model, 1, GL_FALSE, glm::value_ptr(model));

        glBindVertexArray(vao);

        glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindVertexArray(0);

        // Swap the front and back buffers
        glfwSwapBuffers(main_window);
    }
}