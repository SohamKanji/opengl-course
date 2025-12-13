#include "light.h"

Light::Light() : m_color(glm::vec3(1.0,1.0,1.0)), m_ambient_intensity(1.0), m_direction(glm::vec3(0.0, -1.0, 0.0)), m_diffuse_intensity(0.0)
{
}

Light::Light(GLfloat red, GLfloat blue, GLfloat green, GLfloat ambient_intensity, GLfloat x_direction, GLfloat y_direction, GLfloat z_direction, GLfloat diffuse_intensity) : m_color(glm::vec3(red,green,blue)), m_ambient_intensity(ambient_intensity), m_direction(glm::vec3(x_direction, y_direction, z_direction)), m_diffuse_intensity(diffuse_intensity)
{
}


void Light::useLight(GLuint uniform_color_location, GLuint uniform_ambient_intensity_location, GLuint uniform_direction_location, GLuint uniform_diffuse_intensity_location)
{
    glUniform3f(uniform_color_location, m_color.x, m_color.y, m_color.z);
    glUniform1f(uniform_ambient_intensity_location, m_ambient_intensity);
    glUniform3f(uniform_direction_location, m_direction.x, m_direction.y, m_direction.z);
    glUniform1f(uniform_diffuse_intensity_location, m_diffuse_intensity);
}