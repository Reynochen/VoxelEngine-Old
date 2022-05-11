#ifndef WINDOW_WINDOW
#define WINDOW_WINDOW

class GLFWwindow;

class Window {
    static unsigned short fpsLock;
    static double lastTime;
    static int width, height;

    static void fpsLimit();
    static void winSizeCallBack(GLFWwindow* window, int width, int height);

public:
    static GLFWwindow* window;

    static int initialization(int width, int height, const char* title, unsigned short fpsLock = 0);
    static int ShouldClose();
    static void ShouldClose(bool value);

    static void swapBuffers();
    static void terminate();

    static int getWidth();
    static int getHeight();
};

#endif