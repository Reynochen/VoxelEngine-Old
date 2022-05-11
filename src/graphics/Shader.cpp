#include "Shader.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <string>
#include <fstream>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>

Shader::Shader(unsigned int id) : id(id) {
}

Shader::~Shader() {
    glDeleteShader(id);
}

void Shader::use() {
    glUseProgram(id);
}

void Shader::setMatrix(const char* name, glm::mat4 matrix) {
    glUniformMatrix4fv(glGetUniformLocation(id, name), 1, GL_FALSE, glm::value_ptr(matrix));
}

Shader* loadShader(const char* PathVertShader, const char* PathFragShader) {
    std::string vertBuffer;
    std::string fragBuffer;

    std::ifstream file;
    char buffer;
    
    file.open(PathVertShader);
    if(!file) std::cerr << "ERROR::SHADER::VERTEX::FILE_NOT_OPEN\n\n";
    while(file.get(buffer)) vertBuffer += buffer; 
    file.close();
    
    file.open(PathFragShader);
    if(!file) std::cerr << "ERROR::SHADER::FRAGMENT::FILE_NOT_OPEN\n\n";
    while(file.get(buffer)) fragBuffer += buffer;
    file.close();
    
    const char* vertCode = vertBuffer.c_str();
    const char* fragCode = fragBuffer.c_str();


    unsigned int vertShader, fragShader;
    int success;
    char infoLog[512];
    //Vertex shader compile
    vertShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertShader, 1, &vertCode, nullptr);
    glCompileShader(vertShader);

    glGetShaderiv(vertShader, GL_COMPILE_STATUS, &success);
    if(!success) {
        glGetShaderInfoLog(vertShader, 512, nullptr, infoLog);
        std::cout << "ERROR::SHADER::VERTEX compilation failed\n" << infoLog << '\n';
    }
    //Fragment shader compile
    fragShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragShader, 1, &fragCode, nullptr);
    glCompileShader(fragShader);
    
    glGetShaderiv(fragShader, GL_COMPILE_STATUS, &success);
    if(!success) {
        glGetShaderInfoLog(fragShader, 512, nullptr, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT compilation failed\n" << infoLog << '\n';
    }

    unsigned int id = glCreateProgram();
    glAttachShader(id, vertShader);
    glAttachShader(id, fragShader);
    glLinkProgram(id);

    glGetProgramiv(id, GL_LINK_STATUS, &success);
    if(!success) {
        glGetProgramInfoLog(id, 512, nullptr, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM link failed\n" << infoLog << '\n';
    };

    glDeleteShader(vertShader);
    glDeleteShader(fragShader);

    return new Shader(id);
}