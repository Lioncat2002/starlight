//
// Created by Msi on 10/24/2023.
//

#pragma once

#include "detail/type_mat.hpp"
#include "vec3.hpp"

namespace starlight {

    class Math {
    public:
        static glm::mat4 createTransformationMatrix(glm::vec3 translation,glm::vec3 rotation, glm::vec3 scale);
        static glm::mat4 createViewMatrix();
    };

} // starlight
