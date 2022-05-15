#include "VoxRenderer.hpp"

#include "Voxel.hpp"
#include "Chunk/Chunk.hpp"

#include "graphics/Mesh.hpp"

#define VERTEX_SIZE (3 + 2)

#define IS_IN(X, Y, Z) ((X) >= 0 && (X) < CHUNK_W && (Y) >= 0 && (Y) < CHUNK_H && (Z) >= 0 && (Z) < CHUNK_L)
#define VOXEL(X,Y,Z) (chunk->voxels[((Y) * CHUNK_L + (Z)) * CHUNK_W + (X)])
#define IS_BLOCKED(X, Y, Z) (IS_IN(X, Y, Z) && VOXEL(X, Y, Z).id)

#define VERTEX(INDEX, X,Y,Z,   U,V) buffer[INDEX + 0] = (X);\
                                    buffer[INDEX + 1] = (Y);\
                                    buffer[INDEX + 2] = (Z);\
                                    buffer[INDEX + 3] = (U);\
                                    buffer[INDEX + 4] = (V);\
                                    INDEX += VERTEX_SIZE;
int attrs[] {3,2, 0};

VoxRenderer::VoxRenderer(int capacity) {
    buffer = new float[capacity * VERTEX_SIZE * 6];
}

VoxRenderer::~VoxRenderer() {
    delete[] buffer;
}

Mesh* VoxRenderer::render(Chunk* chunk, Chunk** closes) {
    int index = 0;
    float uvSize = 1.0f/16.0f;

    for(int y = 0; y < CHUNK_H; y++)
        for(int z = 0; z < CHUNK_L; z++)
            for (int x = 0; x < CHUNK_W; x++) {
                unsigned int id = VOXEL(x, y, z).id;
                
                if(!id) continue;

                float u = (id % 16) * uvSize;
                float v = 1 - (1 + id / 16) * uvSize;
                float u2 = u + uvSize;
                float v2 = v + uvSize;
                
                bool isBlockChunk = false;
                isBlockChunk = x % 16 == 15 && closes[(1 * 2 + 1) * 2 + 2] != nullptr && closes[(1 * 2 + 1) * 2 + 2]->voxels[(y * CHUNK_L + z) * CHUNK_W + 0].id;
                if(!IS_BLOCKED(x+1, y, z) && !isBlockChunk) { //Right side +X
                    VERTEX(index,   x + 0.5f, y + 0.5f, z - 0.5f,   u2, v2);
                    VERTEX(index,   x + 0.5f, y - 0.5f, z - 0.5f,   u2, v);
                    VERTEX(index,   x + 0.5f, y - 0.5f, z + 0.5f,   u,  v);

                    VERTEX(index,   x + 0.5f, y - 0.5f, z + 0.5f,   u, v);
                    VERTEX(index,   x + 0.5f, y + 0.5f, z + 0.5f,   u, v2);
                    VERTEX(index,   x + 0.5f, y + 0.5f, z - 0.5f,   u2,v2);
                }
                isBlockChunk = y % 16 == 15 && closes[(2 * 2 + 1) * 2 + 1] != nullptr && closes[(2 * 2 + 1) * 2 + 1]->voxels[(0 * CHUNK_L + z) * CHUNK_W + x].id;
                if(!IS_BLOCKED(x, y+1, z) && !isBlockChunk) { //Top side +Y
                    VERTEX(index,   x + 0.5f, y + 0.5f, z - 0.5f,   u, v);
                    VERTEX(index,   x + 0.5f, y + 0.5f, z + 0.5f,   u2, v);
                    VERTEX(index,   x - 0.5f, y + 0.5f, z + 0.5f,   u2, v2);

                    VERTEX(index,   x - 0.5f, y + 0.5f, z + 0.5f,   u2, v2);
                    VERTEX(index,   x - 0.5f, y + 0.5f, z - 0.5f,   u, v2);
                    VERTEX(index,   x + 0.5f, y + 0.5f, z - 0.5f,   u, v);
                }
                isBlockChunk = z % 16 == 15 && closes[(1 * 2 + 2) * 2 + 1] != nullptr && closes[(1 * 2 + 2) * 2 + 1]->voxels[(y * CHUNK_L + 0) * CHUNK_W + x].id;
                if(!IS_BLOCKED(x, y, z+1) && !isBlockChunk) { //Back side +Z
                    VERTEX(index,   x + 0.5f, y + 0.5f, z + 0.5f,   u2, v2);
                    VERTEX(index,   x + 0.5f, y - 0.5f, z + 0.5f,   u2, v);
                    VERTEX(index,   x - 0.5f, y - 0.5f, z + 0.5f,   u, v);

                    VERTEX(index,   x - 0.5f, y - 0.5f, z + 0.5f,   u, v);
                    VERTEX(index,   x - 0.5f, y + 0.5f, z + 0.5f,   u, v2);
                    VERTEX(index,   x + 0.5f, y + 0.5f, z + 0.5f,   u2, v2);
                }

                isBlockChunk = x % 16 == 0 && closes[(1 * 2 + 1) * 2 + 0] != nullptr && closes[(1 * 2 + 1) * 2 + 0]->voxels[(y * CHUNK_L + z) * CHUNK_W + 15].id;
                if(!IS_BLOCKED(x-1, y, z) && !isBlockChunk) { //Left side -X
                    VERTEX(index,   x - 0.5f, y - 0.5f, z + 0.5f,   u, v);
                    VERTEX(index,   x - 0.5f, y - 0.5f, z - 0.5f,   u2, v);
                    VERTEX(index,   x - 0.5f, y + 0.5f, z - 0.5f,   u2, v2);

                    VERTEX(index,   x - 0.5f, y + 0.5f, z - 0.5f,   u2, v2);
                    VERTEX(index,   x - 0.5f, y + 0.5f, z + 0.5f,   u, v2);
                    VERTEX(index,   x - 0.5f, y - 0.5f, z + 0.5f,   u, v);
                }
                isBlockChunk = y % 16 == 0 && closes[(0 * 2 + 1) * 2 + 1] != nullptr && closes[(0 * 2 + 1) * 2 + 1]->voxels[(15 * CHUNK_L + z) * CHUNK_W + x].id;
                if(!IS_BLOCKED(x, y-1, z) && !isBlockChunk) { //Button side -Y
                    VERTEX(index,   x - 0.5f, y - 0.5f, z + 0.5f,   u, v);
                    VERTEX(index,   x + 0.5f, y - 0.5f, z + 0.5f,   u2, v);
                    VERTEX(index,   x + 0.5f, y - 0.5f, z - 0.5f,   u2, v2);

                    VERTEX(index,   x + 0.5f, y - 0.5f, z - 0.5f,   u2, v2);
                    VERTEX(index,   x - 0.5f, y - 0.5f, z - 0.5f,   u, v2);
                    VERTEX(index,   x - 0.5f, y - 0.5f, z + 0.5f,   u, v);
                }
                isBlockChunk = z % 16 == 0 && closes[(1 * 2 + 0) * 2 + 1] != nullptr && closes[(1 * 2 + 0) * 2 + 1]->voxels[(y * CHUNK_L + 15) * CHUNK_W + x].id;
                if(!IS_BLOCKED(x, y, z-1) && !isBlockChunk) { //Front side -Z
                    VERTEX(index,   x - 0.5f, y - 0.5f, z - 0.5f,   u, v);
                    VERTEX(index,   x + 0.5f, y - 0.5f, z - 0.5f,   u2, v);
                    VERTEX(index,   x + 0.5f, y + 0.5f, z - 0.5f,   u2, v2);

                    VERTEX(index,   x + 0.5f, y + 0.5f, z - 0.5f,   u2, v2);
                    VERTEX(index,   x - 0.5f, y + 0.5f, z - 0.5f,   u, v2);
                    VERTEX(index,   x - 0.5f, y - 0.5f, z - 0.5f,   u, v);
                }
            }
    
    return new Mesh(buffer, index / VERTEX_SIZE, attrs);
}