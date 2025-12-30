#pragma once

#include "point_light.h"

class SpotLight : public PointLight
{
public:

    SpotLight();
    SpotLight(GLfloat red, GLfloat blue, GLfloat green, GLfloat ambient_intensity, GLfloat diffuse_intensity, GLfloat x_position, GLfloat y_position, GLfloat z_position, GLfloat quadratic, GLfloat linear, GLfloat constant, GLfloat cutoff_angle, GLfloat x_dir, GLfloat y_dir, GLfloat z_dir);
    void useLight(GLuint uniform_color_location, GLuint uniform_ambient_intensity_location, GLuint uniform_diffuse_intensity_location, GLuint uniform_position_location, GLuint uniform_quadratic_location, GLuint uniform_linear_location, GLuint uniform_constant_location, GLfloat uniform_cutoff_locaton, GLfloat uniform_direction_location);
    void useFlash(glm::vec3 direction, glm::vec3 position);
protected:
    GLfloat m_cutoff;
    glm::vec3 m_direction;
};