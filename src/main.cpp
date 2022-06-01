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

int main() {
    
    Window::initialization(800, 600, "Voxel Engine", 0);
    Events::initialization(Window::window);

    Camera camera(glm::vec3(0,0,0));

    Chunks* chunks = new Chunks(3, 3, 3);
    
    Mesh** meshes = new Mesh*[chunks->volume];
    VoxRenderer renderer(1024 * 1024);

    Chunk* closes[12];
    for(int i = 0; i < chunks->volume; i++) {
        Chunk* chunk = chunks->chunks[i];
        
        for (int i = 0; i < 12; i++)
            closes[i] = nullptr;
        for (int j = 0; j < chunks->volume; j++) {
            
            Chunk* other = chunks->chunks[j];
            int oX = other->x - chunk->x;
            int oY = other->y - chunk->y;
            int oZ = other->z - chunk->z;

            if( abs(oX) > 1 || abs(oY) > 1 || abs(oZ) > 1 ||
                abs(oX) == abs(oZ) && oX != 0 || oX == 0 && oY == 0 && oZ == 0 || oY != 0 && oX != 0 || oY != 0 && oZ != 0) continue;
                
            oX++;
            oY++;
            oZ++;

            closes[(oY * 2 + oZ) * 2 + oX] = other;
        }
        meshes[i] = renderer.render(chunk, closes);
    }
    Mesh* crosshair = new Mesh(vertices, 4, att);
    Shader* crosshairShader = loadShader("../res/Shaders/crosshairShader.vs", "../res/Shaders/crosshairShader.fs");

    Shader* shader = loadShader("../res/Shaders/main.vs", "../res/Shaders/main.fs");
    Texture* texture = loadTexture("../res/Textures/atlas.png");
    
    glEnable(GL_CULL_FACE);
    glFrontFace(GL_CW);

    glm::mat4 model(1.0f);
    glm::mat4 view(1.0f);
    glm::mat4 projection;

    glClearColor(0.1f, 0.4f, 0.5f, 1.0f);
    
    while(!Window::ShouldClose()) {
        camera.update();
        projection = glm::perspective(glm::radians(camera.getFov()), (float)Window::getWidth() / (float)Window::getHeight(), 0.01f, 1024.0f);
        view = camera.getMatrix();

        if(Events::jpressed(GLFW_KEY_ESCAPE))
            Window::ShouldClose(true);

        if(Events::jclicked(GLFW_MOUSE_BUTTON_LEFT)) {
            camera.rayCast(chunks);
            
            for(int i = 0; i < chunks->volume; i++)
                delete meshes[i];
            for(int i = 0; i < chunks->volume; i++) {
                Chunk* chunk = chunks->chunks[i];
            
            for (int i = 0; i < 12; i++)
                closes[i] = nullptr;
            for (int j = 0; j < chunks->volume; j++) {
                
                Chunk* other = chunks->chunks[j];
                int oX = other->x - chunk->x;
                int oY = other->y - chunk->y;
                int oZ = other->z - chunk->z;

                if( abs(oX) > 1 || abs(oY) > 1 || abs(oZ) > 1 ||
                    abs(oX) == abs(oZ) && oX != 0 || oX == 0 && oY == 0 && oZ == 0 || oY != 0 && oX != 0 || oY != 0 && oZ != 0) continue;
                    
                oX++;
                oY++;
                oZ++;

                closes[(oY * 2 + oZ) * 2 + oX] = other;
                }
                meshes[i] = renderer.render(chunk, closes);
            }
        }
        
        shader->use();
        shader->setMatrix("model", model);
        shader->setMatrix("view", view);
        shader->setMatrix("projection", projection);
        texture->bind();
        model = glm::mat4(1.0f);
        for(int i = 0; i < chunks->volume; i++) {
            Chunk* chunk = chunks->chunks[i];
            Mesh* mesh = meshes[i];

            model = glm::translate(glm::mat4(1.0f), glm::vec3(chunk->x * CHUNK_W+0.5f, chunk->y * CHUNK_H+0.5f, chunk->z * CHUNK_L+0.5f));
            shader->setMatrix("model", model);
            mesh->draw(GL_TRIANGLES);
        }

        crosshairShader->use();
        crosshair->draw(GL_LINES);
        Window::swapBuffers();
        Events::pullEvents();
    }

    delete shader;
    delete texture;
    for(int i = 0; i < chunks->volume; i++)
        delete meshes[i];
    delete[] meshes;
    delete chunks;   
    delete crosshairShader;
    delete crosshair;

    Window::terminate();
    return 0;
}