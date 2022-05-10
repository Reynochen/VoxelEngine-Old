#ifndef GRAPHICS_SHADER
#define GRAPHICS_SHADER

class Shader {
    unsigned int id;
public:
    Shader(unsigned int id);
    ~Shader();

    void use();
};

Shader* loadShader(const char* PathVertShader, const char* PathFragShader);

#endif