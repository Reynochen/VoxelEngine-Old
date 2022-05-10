#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "window/Window.hpp"

#include "graphics/Mesh.hpp"

float vertices[] {
    -0.5f, -0.5f, 0.0f,
    0.5f, -0.5f, 0.0f,
    -0.5f, 0.5f, 0.0f,

    -0.5f, 0.5f, 0.0f,
    0.5f, -0.5f, 0.0f,
    0.5f, 0.5f, 0.0f, 
};

int attrs[] {3, 0};

int main() {
    
    Window::initialization(800, 600, "Voxel Engine", 60);

    Mesh mesh(vertices, 6, attrs);

    glClearColor(0.1f, 0.4f, 0.5f, 1.0f);
    while(!Window::winShouldClose()) {
        
        mesh.draw(GL_TRIANGLES);

        Window::swapBuffers();
        glfwPollEvents();
    }

    Window::terminate();
    return 0;
}