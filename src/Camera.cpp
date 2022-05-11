#include "Camera.hpp"

#include <glfw/glfw3.h>

#include "window/Events.hpp"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/glm.hpp>

Camera::Camera( glm::vec3 pos, glm::vec3 worldUp, float fov, float sensitivity, float speed, float yaw, float pitch) :
                pos(pos), worldUp(worldUp), fov(fov), sensitivity(sensitivity), speed(speed), yaw(yaw), pitch(pitch) {
    update();
}

float Camera::getFov() {
    return fov;
}
glm::mat4 Camera::getMatrix() {
    return glm::lookAt(pos, pos + front, up);
}
void Camera::update() {
    yaw += Events::getDeltaX() * sensitivity;
    pitch += Events::getDeltaY() * sensitivity;

    if(pitch > 89.0f)
        pitch = 89.0f;
    if(pitch < -89.0f)
        pitch = -89.0f;
    
    //Update vectors mouse move
    glm::vec3 newFront;
    newFront.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    newFront.y = sin(glm::radians(pitch));
    newFront.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    front = glm::normalize(newFront);

    right = glm::normalize(glm::cross(front, worldUp));
    up = glm::normalize(glm::cross(right, front));
    //Control move
    if(Events::pressed(GLFW_KEY_W))
        pos += front * speed * Events::getDeltaTime();
    if(Events::pressed(GLFW_KEY_S))
        pos -= front * speed * Events::getDeltaTime();
    if(Events::pressed(GLFW_KEY_A))
        pos -= glm::normalize(glm::cross(front, up)) * speed * Events::getDeltaTime();
    if(Events::pressed(GLFW_KEY_D))
        pos += glm::normalize(glm::cross(front, up)) * speed * Events::getDeltaTime();
}