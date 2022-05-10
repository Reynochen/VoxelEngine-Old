#include "Mesh.hpp"

#include <glad/glad.h>
#include <glfw/glfw3.h>

Mesh::Mesh(const float* buffer, unsigned long long vertices, const int* attrs) : vertices(vertices) {
    int vertexSize = 0;
    for (int i = 0; attrs[i]; i++)
        vertexSize += attrs[i];
    

    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);

    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertices * vertexSize, buffer, GL_STATIC_DRAW);
    
    int offset = 0;
    for (int i = 0; attrs[i]; i++) {
        glVertexAttribPointer(i, attrs[i], GL_FLOAT, GL_FALSE, vertexSize * sizeof(float), (void*)(offset * sizeof(float)));
        glEnableVertexAttribArray(i);
        offset += attrs[i];
    }
    
    glBindVertexArray(0);
}

Mesh::~Mesh() {
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
}

void Mesh::draw(int mode) {
    glBindVertexArray(vao);
    glDrawArrays(mode, 0, vertices);
    glBindVertexArray(0);
}