#ifndef GRAPHICS_MESH
#define GRAPHICS_MESH

class Mesh {
    unsigned int vao, vbo;
    unsigned long long vertices;
public:
    Mesh(const float* buffer, unsigned long long vertices, const int* attrs);
    ~Mesh();

    void draw(int mode);
};

#endif