#ifndef CHUNKS
#define CHUNKS

class Chunk;
class Voxel;
#include "glm/vec3.hpp"

class Chunks {
    int w,h,l;

public:
    int volume;
    Chunk** chunks;
    Chunks(int w, int h, int l);
    ~Chunks();

    Voxel* getVoxel(glm::vec3 pos);
    void setVoxel(glm::vec3 pos, int id);

    Chunk* getChunk(const glm::vec3 pos);

    Voxel* rayCast(Chunks* chunks, glm::vec3 pos, glm::vec3 dir, glm::vec3* lastVoxelPos = nullptr, glm::vec3* voxelPos = nullptr, int radius = 5);
};


#endif