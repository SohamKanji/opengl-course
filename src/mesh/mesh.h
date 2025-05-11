#pragma once
#include <GL/glew.h>

class Mesh {
    public:
    Mesh();

    ~Mesh();

    void createMesh(GLfloat *vertices, unsigned int *indices, unsigned int vertex_count, unsigned int index_count);

    void renderMesh();

    void bindVAO();

    void clearMesh();
    private:
    GLuint VAO, VBO, IBO;
    GLsizei index_count;
};