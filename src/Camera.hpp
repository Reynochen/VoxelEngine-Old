#ifndef CAMERA
#define CAMERA

#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>

#define FOV 80.0f
#define YAW 90.0f
#define PITCH 0.0f

#define SENSITIVITY 0.15f
#define SPEED 6.0f

class Shader;

class Camera {
    float fov;

    float pitch;
    float yaw;
    float sensitivity;
    
    float speed;

    glm::vec3 front = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 right;
    glm::vec3 worldUp;
    glm::vec3 up;
    glm::vec3 pos;

public:
    Camera(glm::vec3 pos = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 worldUp = glm::vec3(0.0f, 1.0f, 0.0f), 
    float fov = FOV, float sensitivity = SENSITIVITY, float speed = SPEED, float yaw = YAW, float pitch = PITCH);

    void update();

    float getFov();
    glm::mat4 getMatrix();
};

#endif