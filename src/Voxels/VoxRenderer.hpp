#ifndef VOXRENDERER
#define VOXRENDERER

class Mesh;
class Chunk;

class VoxRenderer {
    float* buffer;
public:
    VoxRenderer(int capacity);
    ~VoxRenderer();

    Mesh* render(Chunk* chunk, Chunk** closes);
};

#endif