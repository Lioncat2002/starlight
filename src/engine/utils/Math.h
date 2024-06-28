//
// Created by Msi on 10/24/2023.
//

#pragma once

#include "detail/type_mat.hpp"
#include "vec3.hpp"
#include "engine/entities/Camera.h"

namespace starlight {

    class Math {
    public:
        static glm::mat4 createTransformationMatrix(glm::vec3 translation,glm::vec3 rotation, glm::vec3 scale);
        static glm::mat4 createViewMatrix(Camera &camera);
        static glm::vec3 moveTowards(const glm::vec3& currentPos, const glm::vec3& targetPos, float deltaTime, float speed);
    };

} // starlight
