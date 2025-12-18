#include "material.h"

Material::Material() : m_shininess(0.0f), m_specular_intensity(0.0f)
{
}

Material::Material(GLfloat shininess, GLfloat specular_intensity) : m_shininess(shininess), m_specular_intensity(specular_intensity)
{
}

void Material::useMaterial(GLuint uniform_shininess_location, GLuint uniform_specular_intensity_location)
{
    glUniform1f(uniform_shininess_location, m_shininess);
    glUniform1f(uniform_specular_intensity_location, m_specular_intensity);
}