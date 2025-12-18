#define STB_IMAGE_IMPLEMENTATION
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
#include "camera.h"
#include "texture.h"
#include "light.h"
#include <iostream>
#include "material.h"

std::vector<Mesh*> mesh_list;
std::vector<Shader*> shader_list;
GLWindow main_window;
Texture brick_texture;
Texture dirt_texture;
Material shiny_material(4.0f, 256.0f);
Material dull_material(0.3f, 4.0f);
Camera camera;
Light light(1.0f, 0.0f, 0.0f, 0.2f, 2.0f, -1.0f, -2.0f, 1.0f);
GLfloat last_time = 0;

static const std::string VERTEX_SHADER = "Shaders/shader.vert";

static const std::string FRAGMENT_SHADER = "Shaders/shader.frag";

void createAverageNormal(unsigned int* indices, GLfloat* vertices, unsigned int vertex_count, unsigned int index_count, unsigned int stride, unsigned int normal_offset)
{
    for(int i=0; i<index_count; i+=3) {
        auto index1 = indices[i], index2 = indices[i+1], index3 = indices[i+2];
        auto vertex_index1 = indices[i]*stride, vertex_index2 = indices[i+1]*stride, vertex_index3 = indices[i+2]*stride;
        auto side1 = glm::vec3(vertices[vertex_index2]-vertices[vertex_index1], vertices[vertex_index2+1]-vertices[vertex_index1+1], vertices[vertex_index2+2]-vertices[vertex_index1+2]);
        auto side2 = glm::vec3(vertices[vertex_index3]-vertices[vertex_index1], vertices[vertex_index3+1]-vertices[vertex_index1+1], vertices[vertex_index3+2]-vertices[vertex_index1+2]);
        auto normal = glm::normalize(glm::cross(side1, side2));
        vertex_index1+=normal_offset;
        vertex_index2+=normal_offset;
        vertex_index3+=normal_offset;
        vertices[vertex_index1] += normal.x; vertices[vertex_index1+1] += normal.y; vertices[vertex_index1+2] += normal.z;
        vertices[vertex_index2] += normal.x; vertices[vertex_index2+1] += normal.y; vertices[vertex_index2+2] += normal.z;
        vertices[vertex_index3] += normal.x; vertices[vertex_index3+1] += normal.y; vertices[vertex_index3+2] += normal.z;
    }
    for(int i=normal_offset; i<vertex_count; i+=stride) {
        auto normalized_normal = glm::normalize(glm::vec3(vertices[i], vertices[i+1], vertices[i+2]));
        vertices[i] = normalized_normal.x;
        vertices[i+1] = normalized_normal.y;
        vertices[i+2] = normalized_normal.z;
    }
}

void createObjects()
{
    unsigned int indices[] = {
        0, 3, 1,
		1, 3, 2,
		2, 3, 0,
		0, 1, 2
    };

    GLfloat vertices[] = {
        -1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
        0.0f, -1.0f, 1.0f,  0.5f, 0.0f, 0.0f, 0.0f, 0.0f,
        1.0f, -1.0f, 0.0f,  1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f,   0.5f, 1.0f, 0.0f, 0.0f, 0.0f
    };
    createAverageNormal(indices, vertices, 32, 12, 8, 5);
    auto obj1 = new Mesh();
    obj1->createMesh(vertices, indices, 32, 12);
    mesh_list.push_back(obj1);

    auto obj2 = new Mesh();
    obj2->createMesh(vertices, indices, 32, 12);
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

    camera = Camera(glm::vec3(0,0,0), glm::vec3(0,1.0f,0), -90.0f, 0.0f, 5.0f, 1.0f);
    createObjects();
    createShaders();

    auto projection = glm::perspective(45.0f, main_window.getBufferWidth() / main_window.getBufferHeight(), 0.1f, 100.0f);
    GLuint uniform_model = 0, uniform_projection = 0, uniform_view = 0, uniform_color = 0, uniform_ambient_intensity = 0,
    uniform_direction = 0, uniform_diffuse_intensity = 0, uniform_eye_position = 0, uniform_specular_intensity = 0, uniform_shininess = 0;

    brick_texture = Texture("Textures/brick.png");
    brick_texture.loadTexture();
    dirt_texture = Texture("Textures/dirt.png");
    dirt_texture.loadTexture();
    // Loop until window closed
    while(!main_window.shouldClose())
    {
        // Get + Handle user input events
        glfwPollEvents();
        auto current_time = glfwGetTime();
        auto delta_time = current_time - last_time;
        last_time = current_time;
        camera.handleKeyPress(main_window.getKeys(), delta_time);
        camera.handleMouseMove(main_window.getXChange(), main_window.getYChange());

        // Clear window
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shader_list[0]->useShader();
        light.useLight(shader_list[0]->getUniformColor(), shader_list[0]->getUniformAmbientIntensity(), shader_list[0]->getUniformDirection(), shader_list[0]->getUniformDiffuseIntensity());
        uniform_model = shader_list[0]->getUniformModel();
        uniform_projection = shader_list[0]->getUniformProjection();
        uniform_view = shader_list[0]->getUnifromView();
        uniform_color = shader_list[0]->getUniformColor();
        uniform_ambient_intensity = shader_list[0]->getUniformAmbientIntensity();
        uniform_direction = shader_list[0]->getUniformDirection();
        uniform_diffuse_intensity = shader_list[0]->getUniformDiffuseIntensity();
        uniform_eye_position = shader_list[0]->getUniformEyePosition();
        uniform_specular_intensity = shader_list[0]->getUniformSpecularIntensity();
        uniform_shininess = shader_list[0]->getUniformShininess();

        glUniformMatrix4fv(uniform_projection, 1, GL_FALSE, glm::value_ptr(projection));
        glUniformMatrix4fv(uniform_view, 1, GL_FALSE, glm::value_ptr(camera.getViewMatrix()));
        glUniform3f(uniform_eye_position, camera.getCameraPosition().x, camera.getCameraPosition().y, camera.getCameraPosition().z);

        glm::mat4 model(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, 0.0f, -2.5f));
        model = glm::scale(model, glm::vec3(0.4f, 0.4f, 1.0f));
        glUniformMatrix4fv(uniform_model, 1, GL_FALSE, glm::value_ptr(model));
        
        light.useLight(uniform_color, uniform_ambient_intensity, uniform_direction, uniform_diffuse_intensity);

        brick_texture.useTexture();
        shiny_material.useMaterial(uniform_shininess, uniform_specular_intensity);
        mesh_list[0]->renderMesh();

        model = glm::mat4(5.0f);
        model = glm::translate(model, glm::vec3(0.0f, 1.0f, -2.5f));
        model = glm::scale(model, glm::vec3(0.4f, 0.4f, 1.0f));
        glUniformMatrix4fv(uniform_model, 1, GL_FALSE, glm::value_ptr(model));
        dirt_texture.useTexture();
        dull_material.useMaterial(uniform_shininess, uniform_specular_intensity);
        mesh_list[1]->renderMesh();

        glUseProgram(0);

        // Swap the front and back buffers
        main_window.swapBuffers();
    }
}