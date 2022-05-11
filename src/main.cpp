#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "window/Window.hpp"

#include "graphics/Mesh.hpp"
#include "graphics/Shader.hpp"
#include "graphics/Texture.hpp"

float vertices[] {
    -0.5f, -0.5f, 0.0f,     0, 0,
    0.5f, -0.5f, 0.0f,      1, 0,
    -0.5f, 0.5f, 0.0f,      0, 1,

    -0.5f, 0.5f, 0.0f,      0, 1,
    0.5f, -0.5f, 0.0f,      1, 0,
    0.5f, 0.5f, 0.0f,       1, 1,
};

int attrs[] {3, 2, 0};

int main() {
    
    Window::initialization(800, 600, "Voxel Engine", 60);

    Mesh mesh(vertices, 6, attrs);
    Shader* shader = loadShader("../res/Shaders/main.vs", "../res/Shaders/main.fs");
    Texture* tex = loadTexture("dirt.png");

    glClearColor(0.1f, 0.4f, 0.5f, 1.0f);
    while(!Window::winShouldClose()) {
        
        shader->use();
        tex->bind();
        mesh.draw(GL_TRIANGLES);

        Window::swapBuffers();
        glfwPollEvents();
    }

    Window::terminate();
    return 0;
}