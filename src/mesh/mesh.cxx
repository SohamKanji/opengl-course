#include "mesh.h"

Mesh::Mesh() {
    VAO = 0;
    VBO = 0;
    IBO = 0;
    index_count = 0;
}

void Mesh::createMesh(GLfloat *vertices, unsigned int *indices, unsigned int vertex_count, unsigned int index_count)
{
    this->index_count = index_count;

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &IBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0])*index_count, indices, GL_STATIC_DRAW);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0])*vertex_count, vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void Mesh::bindVAO()
{
    glBindVertexArray(VAO);
}

void Mesh::renderMesh()
{
    glBindVertexArray(VAO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
    glDrawElements(GL_TRIANGLES, index_count, GL_UNSIGNED_INT, nullptr);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    
}

void Mesh::clearMesh()
{
    if(IBO != 0) {
        glDeleteBuffers(1, &IBO);
        IBO = 0;
    }

    if(VBO != 0) {
        glDeleteBuffers(1, &VBO);
        VBO = 0;
    }

    if(VAO != 0) {
        glDeleteVertexArrays(1, &VAO);
        VAO = 0;
    }

    index_count = 0;
}

Mesh::~Mesh()
{
    clearMesh();
}