#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>

class Light
{
public:

    Light();
    Light(GLfloat red, GLfloat blue, GLfloat green, GLfloat ambient_intensity, GLfloat diffuse_intensity);

    void useLight(GLuint uniform_color_location, GLuint uniform_ambient_intensity_location, GLuint uniform_diffuse_intensity_location); 

protected:

    glm::vec3 m_color;
    GLfloat m_ambient_intensity;
    GLfloat m_diffuse_intensity;
};