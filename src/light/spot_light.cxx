#include "spot_light.h"
#include <cmath>

SpotLight::SpotLight() : PointLight(), m_cutoff(1), m_direction(glm::vec3(0.0, -1.0, 0.0))
{
}

SpotLight::SpotLight(GLfloat red, GLfloat blue, GLfloat green, GLfloat ambient_intensity, GLfloat diffuse_intensity, GLfloat x_position, GLfloat y_position, GLfloat z_position, GLfloat quadratic, GLfloat linear, GLfloat constant, GLfloat cutoff_angle, GLfloat x_dir, GLfloat y_dir, GLfloat z_dir) : PointLight(red, blue, green, ambient_intensity, diffuse_intensity, x_position, y_position, z_position, quadratic, linear, constant), m_cutoff(std::cosf(cutoff_angle)), m_direction(glm::normalize(glm::vec3(x_dir, y_dir, z_dir)))
{
}

void SpotLight::useLight(GLuint uniform_color_location, GLuint uniform_ambient_intensity_location, GLuint uniform_diffuse_intensity_location, GLuint uniform_position_location, GLuint uniform_quadratic_location, GLuint uniform_linear_location, GLuint uniform_constant_location, GLfloat uniform_cutoff_locaton, GLfloat uniform_direction_location)
{
    PointLight::useLight(uniform_color_location, uniform_ambient_intensity_location, uniform_diffuse_intensity_location, uniform_position_location, uniform_quadratic_location, uniform_linear_location, uniform_constant_location);
    glUniform1f(uniform_cutoff_locaton, m_cutoff);
    glUniform3f(uniform_direction_location, m_direction.x, m_direction.y, m_direction.z);
}

void SpotLight::useFlash(glm::vec3 direction, glm::vec3 position)
{
    m_direction = direction;
    m_position = position;
}