//
// Created by shubh on 12/11/2021.
//

#pragma once
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera {
public:
    glm::vec3 position;
    Camera() {
        position = glm::vec3(0,0,0);
    }
};