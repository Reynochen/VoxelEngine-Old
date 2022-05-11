#ifndef WINDOW_WINDOW
#define WINDOW_WINDOW

class GLFWwindow;

class Window {
    static GLFWwindow* window;
    static unsigned short fpsLock;
    static double lastTime;
    
    static int width, height;

    static void fpsLimit();

    static void winSizeCallBack(GLFWwindow* window, int width, int height);

public:
    static int initialization(int width, int height, const char* title, unsigned short fpsLock = 0);
    static int winShouldClose();

    static void swapBuffers();
    static void terminate();
};

#endif