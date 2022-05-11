#ifndef GRAPHICS_SHADER
#define GRAPHICS_SHADER

#include <glm/mat4x4.hpp>

class Shader {
    unsigned int id;
public:
    Shader(unsigned int id);
    ~Shader();

    void use();
    void setMatrix(const char* name, glm::mat4 matrix);
};

Shader* loadShader(const char* PathVertShader, const char* PathFragShader);

#endif