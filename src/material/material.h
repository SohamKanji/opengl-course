#pragma once

#include <GL/glew.h>

class Material
{
public:
    Material();

    Material(GLfloat shininess, GLfloat specular_intensity);

    void useMaterial(GLuint uniform_shininess_location, GLuint uniform_specular_intensity_location);
private:
    GLfloat m_shininess;
    GLfloat m_specular_intensity;
};