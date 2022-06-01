#ifndef CHUNKSCONTROLLER
#define CHUNKSCONTROLLER

class Chunks;
class Mesh;
class VoxRenderer;
class Shader;

#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>

class ChunksController {
    Mesh** meshes;
    static VoxRenderer renderer;

public:
    Chunks* chunks;
    ChunksController();
    ~ChunksController();

    void update(glm::vec3 pos);
    void draw(Shader* shader, glm::mat4* model);
};

#endif