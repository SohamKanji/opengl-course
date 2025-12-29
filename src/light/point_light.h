#pragma once

#include "light.h"

class PointLight : public Light 
{
public:

    PointLight();
    PointLight(GLfloat red, GLfloat blue, GLfloat green, GLfloat ambient_intensity, GLfloat diffuse_intensity, GLfloat x_position, GLfloat y_position, GLfloat z_position, GLfloat quadratic, GLfloat linear, GLfloat constant);
    void useLight(GLuint uniform_color_location, GLuint uniform_ambient_intensity_location, GLuint uniform_diffuse_intensity_location, GLuint uniform_position_location, GLuint uniform_quadratic_location, GLuint uniform_linear_location, GLuint uniform_constant_location);
private:
    glm::vec3 m_position;
    GLfloat m_quadratic;
    GLfloat m_linear;
    GLfloat m_constant;
};