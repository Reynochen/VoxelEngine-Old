#include "Texture.hpp"

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <stb_image/stb_image.h>

Texture::Texture(unsigned int id) : id(id) {
}

Texture::~Texture() {
    glDeleteTextures(1, &id);
}

Texture* loadTexture(const char* pathTex) {
    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    
    stbi_set_flip_vertically_on_load(true);
    int width, height, nrChannel;
    unsigned char* data = stbi_load(pathTex, &width, &height, &nrChannel, 0);
    
    if(data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        //glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
        std::cerr << "Failed to load texture.\n";

    stbi_image_free(data);

    return new Texture(texture);
}

void Texture::bind() {
    glBindTexture(GL_TEXTURE_2D, id);
}