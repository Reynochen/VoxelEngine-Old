#include "Camera.hpp"

#include <glfw/glfw3.h>

#include "window/Events.hpp"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/glm.hpp>

#include "Voxels/Voxel.hpp"
#include "Voxels/Chunk/Chunks.hpp"

#include <iostream>

Camera::Camera( glm::vec3 pos, glm::vec3 worldUp, float fov, float sensitivity, float speed, float yaw, float pitch) :
                pos(pos), worldUp(worldUp), fov(fov), sensitivity(sensitivity), speed(speed), yaw(yaw), pitch(pitch) {
    update();
}


//https://stackoverflow.com/questions/55263298/draw-all-voxels-that-pass-through-a-3d-line-in-3d-voxel-space

//https://gamedev.stackexchange.com/questions/72120/how-do-i-find-voxels-along-a-ray
//https://gamedev.stackexchange.com/questions/47362/cast-ray-to-select-block-in-voxel-game?rq=1
//ÍÀÊÎÍÅÖ ÒÎ ÎÍÎ ÐÀÁÎÒÀÅÒ
bool Camera::rayCast(Chunks* chunks, int radius) {
    glm::vec3 startPos(pos.x, pos.y, pos.z);

    glm::vec3 rayPos(startPos);
    glm::vec3 dir = front;

    glm::vec3 step(dir.x>0 ? 1:-1, dir.y>0 ? 1:-1, dir.z>0 ? 1:-1);
    glm::vec3 cellBoundary((int)rayPos.x + (step.x>0 ? 1:0), (int)rayPos.y + (step.y>0 ? 1:0), (int)rayPos.z + (step.z>0 ? 1:0));

    glm::vec3 tMax((cellBoundary.x - rayPos.x) / dir.x, (cellBoundary.y - rayPos.y) / dir.y, (cellBoundary.z - rayPos.z) / dir.z);
    glm::vec3 tDelta(abs(1/dir.x), abs(1/dir.y), abs(1/dir.z));

    float radiusNow = 0.0f;
    while(radiusNow < radius) {
        if(chunks->getVoxel(rayPos) == nullptr) return false;
        if(chunks->getVoxel(rayPos)->id != 0) {
            chunks->setVoxel(rayPos, 0);
            return true;
        }
        if(tMax.x < tMax.y) {
            if(tMax.x < tMax.z) {
                rayPos.x += step.x;
                radiusNow = tMax.x;
                tMax.x += tDelta.x;
            }
            else {
                rayPos.z += step.z;
                radiusNow = tMax.z;
                tMax.z += tDelta.z;
            }
        }
        else {
            if(tMax.y < tMax.z) {
                rayPos.y += step.y;
                radiusNow = tMax.y;
                tMax.y += tDelta.y;
            }
            else {
                rayPos.z += step.z;
                radiusNow = tMax.z;
                tMax.z += tDelta.z;
            }
        }
    }
    
	return false;
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
    glm::vec3 dirMove = glm::vec3(cos(glm::radians(yaw)), 0.0f, sin(glm::radians(yaw)));

    if(Events::pressed(GLFW_KEY_W))
        pos += dirMove * speed * Events::getDeltaTime();
    if(Events::pressed(GLFW_KEY_S))
        pos -= dirMove * speed * Events::getDeltaTime();
    if(Events::pressed(GLFW_KEY_A))
        pos -= glm::normalize(glm::cross(dirMove, up)) * speed * Events::getDeltaTime();
    if(Events::pressed(GLFW_KEY_D))
        pos += glm::normalize(glm::cross(dirMove, up)) * speed * Events::getDeltaTime();

    if(Events::pressed(GLFW_KEY_SPACE))
        pos += worldUp * speed * Events::getDeltaTime();
    if(Events::pressed(GLFW_KEY_LEFT_SHIFT))
        pos -= worldUp * speed * Events::getDeltaTime();
}