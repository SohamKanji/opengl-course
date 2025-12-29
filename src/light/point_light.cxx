#include "point_light.h"

PointLight::PointLight() : Light(), m_position(0.0, 0.0, 0.0), m_quadratic(0.0), m_linear(0.0), m_constant(1.0)
{
}

PointLight::PointLight(GLfloat red, GLfloat blue, GLfloat green, GLfloat ambient_intensity, GLfloat diffuse_intensity, GLfloat x_position, GLfloat y_position, GLfloat z_position, GLfloat quadratic, GLfloat linear, GLfloat constant) 
            : Light(red, blue, green, ambient_intensity, diffuse_intensity), m_position(x_position, y_position, z_position), m_quadratic(quadratic), m_linear(linear), m_constant(constant)
{
}

void PointLight::useLight(GLuint uniform_color_location, GLuint uniform_ambient_intensity_location, GLuint uniform_diffuse_intensity_location, GLuint uniform_position_location, GLuint uniform_quadratic_location, GLuint uniform_linear_location, GLuint uniform_constant_location)
{
    Light::useLight(uniform_color_location, uniform_ambient_intensity_location, uniform_diffuse_intensity_location);
    glUniform3f(uniform_position_location, m_position.x, m_position.y, m_position.z);
    glUniform1f(uniform_quadratic_location, m_quadratic);
    glUniform1f(uniform_linear_location, m_linear);
    glUniform1f(uniform_constant_location, m_constant);
}