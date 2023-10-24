//
// Created by Msi on 10/24/2023.
//

#include "Math.h"
#include "gtc/matrix_transform.hpp"

namespace starlight {

    glm::mat4 Math::createTransformationMatrix(glm::vec3 translation, glm::vec3 rotation, glm::vec3 scale) {
        glm::mat4 matrix = glm::mat4(1.0f); // Initialize as identity matrix
        matrix = glm::translate(matrix, translation);

        matrix = glm::rotate(matrix, glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f)); // Rotation around the X-axis
        matrix = glm::rotate(matrix, glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f)); // Rotation around the Y-axis
        matrix = glm::rotate(matrix, glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f)); // Rotation around the Z-axis

        matrix = glm::scale(matrix, scale);
        return matrix;
    }

    glm::mat4 Math::createViewMatrix(Camera &camera) {
        glm::mat4 viewMatrix=glm::lookAt(camera.getPosition(),camera.getPosition()+glm::vec3(0.0f,0.0f,-1.0f),{0.0f,1.0f,0.0f});

        return viewMatrix;
    }
} // starlight