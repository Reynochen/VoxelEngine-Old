#ifndef EVENTS
#define EVENTS

class GLFWwindow;

class Events {
    static bool keys[1037];
    static float deltaTime;
    static float lastFrame;
    //Mouse
    static bool firstMouse;
    static float deltaX,deltaY, lastX,lastY;

    static void keyCallBack(GLFWwindow* window, int key, int scancode, int action, int mods);
    static void mouseButtonCallBack(GLFWwindow* window, int button, int action, int mods);
    static void cursorPosCallBack(GLFWwindow* window, double xpos, double ypos);

public:
    static void initialization(GLFWwindow* window);
    static void pullEvents();

    static bool pressed(int key);
    static bool jpressed(int key);

    static bool clicked(int button);
    static bool jclicked(int button);

    static float getDeltaX(), getDeltaY();
    static float getDeltaTime();
};

#endif