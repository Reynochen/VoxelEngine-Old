#ifndef GRAPHICS_TEXTURE
#define GRAPHICS_TEXTURE

class Texture {
    unsigned int id;
public:
    Texture(unsigned int id);
    ~Texture();

    void bind();
};

Texture* loadTexture(const char* pathTex);

#endif