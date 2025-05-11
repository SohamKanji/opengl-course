#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include "mesh.h"
#include "shader.h"
#include "glwindow.h"

std::vector<Mesh*> mesh_list;
std::vector<Shader*> shader_list;
GLWindow main_window;

static const std::string VERTEX_SHADER = "Shaders/shader.vert";

static const std::string FRAGMENT_SHADER = "Shaders/shader.frag";

void createObjects()
{
    unsigned int indices[] = {
        0, 1, 2,
        0, 2, 3,
        3, 1, 2,
        0, 1, 3
    };

    GLfloat vertices[] = {
        -1.0f, -1.0f, 0.0f,
        0.0f, -1.0f, 1.0f,
        1.0f, -1.0f, 0.0f,
        0.0f, 1.0f, 0.0f
    };

    auto obj1 = new Mesh();
    obj1->createMesh(vertices, indices, 12, 12);
    mesh_list.push_back(obj1);

    auto obj2 = new Mesh();
    obj2->createMesh(vertices, indices, 12, 12);
    mesh_list.push_back(obj2);
}

void createShaders()
{
    auto shader = new Shader();
    shader->createFromFiles(VERTEX_SHADER, FRAGMENT_SHADER);
    shader_list.push_back(shader);
}

int main() 
{
    main_window = GLWindow(800, 600);
    main_window.initialize();
    createObjects();
    createShaders();

    auto projection = glm::perspective(45.0f, main_window.getBufferWidth() / main_window.getBufferHeight(), 0.1f, 100.0f);
    GLuint uniform_model = 0, uniform_projection = 0;
    
    // Loop until window closed
    while(!main_window.shouldClose())
    {
        // Get + Handle user input events
        glfwPollEvents();

        // Clear window
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shader_list[0]->useShader();
        uniform_model = shader_list[0]->getUniformModel();
        uniform_projection = shader_list[0]->getUniformProjection();

        glm::mat4 model(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, 0.0f, -2.5f));
        model = glm::scale(model, glm::vec3(0.4f, 0.4f, 1.0f));
        glUniformMatrix4fv(uniform_model, 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(uniform_projection, 1, GL_FALSE, glm::value_ptr(projection));

        mesh_list[0]->renderMesh();

        model = glm::mat4(5.0f);
        model = glm::translate(model, glm::vec3(0.0f, 1.0f, -2.5f));
        model = glm::scale(model, glm::vec3(0.4f, 0.4f, 1.0f));
        glUniformMatrix4fv(uniform_model, 1, GL_FALSE, glm::value_ptr(model));
        mesh_list[1]->renderMesh();

        glUseProgram(0);

        // Swap the front and back buffers
        main_window.swapBuffers();
    }
}