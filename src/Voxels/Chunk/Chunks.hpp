#ifndef CHUNKS
#define CHUNKS

class Chunk;
class Voxel;
#include "glm/vec3.hpp"

class Chunks {
    int w,h,l;

public:
    Chunk** chunks;
    int volume;
    Chunks(int w, int h, int l);
    ~Chunks();

    Voxel* getVoxel(glm::vec3 pos);
    void setVoxel(glm::vec3 pos, int id);
};


#endif