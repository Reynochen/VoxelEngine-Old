#ifndef CHUNK
#define CHUNK

#include "voxels/Voxel.hpp"

#define CHUNK_H 16
#define CHUNK_W 16
#define CHUNK_L 16

#define CHUNK_SIZE (CHUNK_H * CHUNK_W * CHUNK_L)

class Chunk {
public:
    bool modified = false;

    int x,y,z;
    Voxel* voxels;
    Chunk(int x, int y, int z);
    ~Chunk();
};


#endif