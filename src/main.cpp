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

#include "Voxels/Chunk/Chunk.hpp"
#include "Voxels/VoxRenderer.hpp"
#include "Voxels/Chunk/Chunks.hpp"

#include "Voxels/Chunk/ChunksController.hpp"

#include "Camera.hpp"

float vertices[] {
    -0.01f, -0.01f,
    0.01f, 0.01f,

    -0.01f, 0.01f,
    0.01f, -0.01f,
};

int att[] {
    2, 0
};

int selectBlock = 1;

int main() {
    
    Window::initialization(800, 600, "Voxel Engine", 0);
    Events::initialization(Window::window);

    Camera camera(glm::vec3(0,0,0));

    ChunksController ChunksCon;

    Mesh* crosshair = new Mesh(vertices, 4, att);
    Shader* crosshairShader = loadShader("../res/Shaders/crosshairShader.vs", "../res/Shaders/crosshairShader.fs");
    
    Shader* shader = loadShader("../res/Shaders/main.vs", "../res/Shaders/main.fs");
    Texture* texture = loadTexture("../res/Textures/atlas.png");

    glm::mat4 model(1.0f);
    glm::mat4 view(1.0f);
    glm::mat4 projection;

    glClearColor(0.1f, 0.4f, 0.5f, 1.0f);
    
    while(!Window::ShouldClose()) {
        camera.update();
        projection = glm::perspective(glm::radians(camera.getFov()), (float)Window::getWidth() / (float)Window::getHeight(), 0.01f, 1024.0f);
        view = camera.getMatrix();
        
        if(Events::jpressed(GLFW_KEY_1)) selectBlock = 1;
        if(Events::jpressed(GLFW_KEY_2)) selectBlock = 2;
        
        if(Events::jpressed(GLFW_KEY_ESCAPE))
            Window::ShouldClose(true);

        if(Events::jclicked(GLFW_MOUSE_BUTTON_LEFT)) {
            glm::vec3 voxelPos;
            Voxel* voxel = ChunksCon.chunks->rayCast(ChunksCon.chunks, camera.getPos(), camera.getFront(), nullptr, &voxelPos);
            if(voxel != nullptr) {
                voxel->id = 0;
                ChunksCon.update(voxelPos);
            }
        } 
        if (Events::jclicked(GLFW_MOUSE_BUTTON_RIGHT)) {
            glm::vec3 lastVoxel;
            if(ChunksCon.chunks->rayCast(ChunksCon.chunks, camera.getPos(), camera. getFront(), &lastVoxel) != nullptr) {
                Voxel* voxel = ChunksCon.chunks->getVoxel(lastVoxel);
                if(voxel != nullptr && voxel->id == 0 && floor(camera.getPos()) != floor(lastVoxel)) {
                    voxel->id = selectBlock;
                    ChunksCon.update(lastVoxel);
                }
            }
        }
        
        shader->use();
        shader->setMatrix("model", model);
        shader->setMatrix("view", view);
        shader->setMatrix("projection", projection);
        texture->bind();

        ChunksCon.draw(shader, &model);

        crosshairShader->use();
        crosshair->draw(GL_LINES);
        Window::swapBuffers();
        Events::pullEvents();
    }

    delete shader;
    delete texture;
     
    delete crosshairShader;
    delete crosshair;

    Window::terminate();
    return 0;
}