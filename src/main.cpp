#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <vector>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "window/Window.hpp"
#include "window/Events.hpp"

#include "graphics/Mesh.hpp"
#include "graphics/Shader.hpp"
#include "graphics/Texture.hpp"

#include "Camera.hpp"

float vertices[] {
    -0.5f, -0.5f, 0.0f,     0, 0,
    0.5f, -0.5f, 0.0f,      1, 0,
    -0.5f, 0.5f, 0.0f,      0, 1,

    -0.5f, 0.5f, 0.0f,      0, 1,
    0.5f, -0.5f, 0.0f,      1, 0,
    0.5f, 0.5f, 0.0f,       1, 1,
};

int attrs[] {3,2, 0};

int main() {
    
    Window::initialization(800, 600, "Voxel Engine", 0);
    Events::initialization(Window::window);
    
    Mesh mesh(vertices, 6, attrs);
    Shader* shader = loadShader("../res/Shaders/main.vs", "../res/Shaders/main.fs");
    Texture* texture = loadTexture("dirt.png");
    
    Camera camera(glm::vec3(0,0,-3));

    glm::mat4 model(1.0f);
    glm::mat4 view(1.0f);
    glm::mat4 projection;

    glClearColor(0.1f, 0.4f, 0.5f, 1.0f);
    while(!Window::ShouldClose()) {
        camera.update();
        projection = glm::perspective(glm::radians(camera.getFov()), (float)Window::getWidth() / (float)Window::getHeight(), 0.01f, 100.0f);
        view = camera.getMatrix();

        if(Events::jpressed(GLFW_KEY_ESCAPE))
            Window::ShouldClose(true);

        shader->use();
        shader->setMatrix("model", model);
        shader->setMatrix("view", view);
        shader->setMatrix("projection", projection);
        texture->bind();
        mesh.draw(GL_TRIANGLES);
        
        Window::swapBuffers();
        Events::pullEvents();
    }

    delete shader;
    delete texture;

    Window::terminate();
    return 0;
}