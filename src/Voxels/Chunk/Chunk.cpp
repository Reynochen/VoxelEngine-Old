#include "Chunk.hpp"

#define VOX(X, Y, Z) (voxels[((Y) * CHUNK_L + (Z)) * CHUNK_W + (X)])

#include <math.h>

Chunk::Chunk(int x, int y, int z) : x(x), y(y), z(z) {
    voxels = new Voxel[CHUNK_SIZE];
    for(int y = 0; y < CHUNK_H; y++)
        for(int z = 0; z < CHUNK_L; z++)
            for(int x = 0; x < CHUNK_W; x++) {
                int realX = x + this->x * CHUNK_W;
                int realY = y + this->y * CHUNK_H;
                int realZ = z + this->z * CHUNK_L;

                int id = 0;
                
                if(realY <= (cos(realX) + 1.5f) * 8.0f) id = 1;

                if(realY < 2) id = 2;

                VOX(x, y, z).id = id;
            }
}

Chunk::~Chunk() {
    delete[] voxels;
}