#pragma once
#include "light.h"

class DirectionalLight : public Light
{
public:

    DirectionalLight();
    DirectionalLight(GLfloat red, GLfloat blue, GLfloat green, GLfloat ambient_intensity, GLfloat diffuse_intensity, GLfloat x_direction, GLfloat y_direction, GLfloat z_direction);

    void useLight(GLuint uniform_color_location, GLuint uniform_ambient_intensity_location, GLuint uniform_diffuse_intensity_location, GLuint uniform_direction_location); 

private:

    glm::vec3 m_direction;
};