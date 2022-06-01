#include "ChunksController.hpp"

#include "Voxels/Voxel.hpp"
#include "Voxels/VoxRenderer.hpp"
#include "Voxels/Chunk/Chunk.hpp"
#include "Voxels/Chunk/Chunks.hpp"

#include "graphics/Mesh.hpp"
#include "graphics/Shader.hpp"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/vec3.hpp>
#include <GLFW/glfw3.h>

VoxRenderer ChunksController::renderer(1024 * 1024);

ChunksController::ChunksController() {
    chunks = new Chunks(3, 3, 3);
    meshes = new Mesh*[chunks->volume];

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
}

ChunksController::~ChunksController() {
    delete chunks;
    for (int i = 0; i < chunks->volume; i++) {
        delete meshes[i]; 
    }
    delete[] meshes;
}

void ChunksController::update(glm::vec3 pos) {
    if(chunks->getChunk(pos) != nullptr) chunks->getChunk(pos)->modified = true;
    if(chunks->getChunk(pos - glm::vec3(1,0,0)) != nullptr) chunks->getChunk(pos - glm::vec3(1,0,0))->modified = true;
    if(chunks->getChunk(pos - glm::vec3(0,1,0)) != nullptr) chunks->getChunk(pos - glm::vec3(0,1,0))->modified = true;
    if(chunks->getChunk(pos - glm::vec3(0,0,1)) != nullptr) chunks->getChunk(pos - glm::vec3(0,0,1))->modified = true;

    if(chunks->getChunk(pos + glm::vec3(1,0,0)) != nullptr) chunks->getChunk(pos + glm::vec3(1,0,0))->modified = true;
    if(chunks->getChunk(pos + glm::vec3(0,1,0)) != nullptr) chunks->getChunk(pos + glm::vec3(0,1,0))->modified = true;
    if(chunks->getChunk(pos + glm::vec3(0,0,1)) != nullptr) chunks->getChunk(pos + glm::vec3(0,0,1))->modified = true;

    Chunk* closes[12];
    for (int i = 0; i < chunks->volume; i++) {
        if(chunks->chunks[i]->modified) {
            chunks->chunks[i]->modified = false;
            delete meshes[i];
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
}

void ChunksController::draw(Shader* shader, glm::mat4* model) {
    for(int i = 0; i < chunks->volume; i++) {
        Chunk* chunk = chunks->chunks[i];
        Mesh* mesh = meshes[i];

        *model = glm::translate(glm::mat4(1.0f), glm::vec3(chunk->x * CHUNK_W+0.5f, chunk->y * CHUNK_H+0.5f, chunk->z * CHUNK_L+0.5f));
        shader->setMatrix("model", *model);
        mesh->draw(GL_TRIANGLES);
    }
}
