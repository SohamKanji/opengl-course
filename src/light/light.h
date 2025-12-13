#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>

class Light
{
public:

    Light();
    Light(GLfloat red, GLfloat blue, GLfloat green, GLfloat ambient_intensity);

    void useLight(GLuint uniform_color_location, GLuint uniform_ambient_intensity_location); 

private:

    glm::vec3 m_color;
    GLfloat m_ambient_intensity;
};