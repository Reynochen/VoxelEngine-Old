#version 330 core

in vec2 aTexCoord;
in vec3 aPos;

out vec2 TexCoord;

void main() {
    gl_Position = vec4(aPos, 1.0);
    TexCoord = aTexCoord;
}