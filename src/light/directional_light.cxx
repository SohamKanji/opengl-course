#include "directional_light.h"

DirectionalLight::DirectionalLight() : Light(), m_direction(glm::vec3(0.0, -1.0, 0.0))
{
}

DirectionalLight::DirectionalLight(GLfloat red, GLfloat blue, GLfloat green, GLfloat ambient_intensity, GLfloat diffuse_intensity, GLfloat x_direction, GLfloat y_direction, GLfloat z_direction) :
                    Light(red, blue, green, ambient_intensity, diffuse_intensity), m_direction(glm::vec3(x_direction, y_direction, z_direction))
{
}


void DirectionalLight::useLight(GLuint uniform_color_location, GLuint uniform_ambient_intensity_location, GLuint uniform_diffuse_intensity_location, GLuint uniform_direction_location)
{
    Light::useLight(uniform_color_location, uniform_ambient_intensity_location, uniform_diffuse_intensity_location);
    glUniform3f(uniform_direction_location, m_direction.x, m_direction.y, m_direction.z);
}