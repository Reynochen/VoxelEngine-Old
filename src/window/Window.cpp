#include "Window.hpp"

#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <iostream>

GLFWwindow* Window::window;

unsigned short Window::fpsLock;
double Window::lastTime = 0;

int Window::initialization(int width, int height, const char* title, unsigned short fpsLock){
    if(!glfwInit()) {
        std::cout << "GLFW initialization failed.\n";
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(width, height, title, nullptr, nullptr);
    if(!window) {
        std::cout << "Window create failed.\n";
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(0);

    if(!gladLoadGL()){
        std::cout << "GLAD initialization failed.\n";
        glfwTerminate();
        return -1;
    } 
    
    glEnable(GL_DEPTH_TEST);

    Window::fpsLock = fpsLock;

    return 0;
}

int Window::winShouldClose() {
    return glfwWindowShouldClose(window);
}

void Window::swapBuffers() {
    glfwSwapBuffers(window);
    fpsLimit();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Window::fpsLimit() {
    //Vsync on crutches
    while(glfwGetTime() < lastTime + 1.0/fpsLock && fpsLock != 0) {}
    lastTime += 1.0/fpsLock;
}

void Window::terminate() {
    glfwTerminate();
}