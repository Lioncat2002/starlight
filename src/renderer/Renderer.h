#pragma once

#include "detail/type_mat.hpp"
#include "detail/type_mat4x4.hpp"

namespace starlight {

    class Renderer {
    private:
        float FOV;
        float NEAR_PLANE;
        float FAR_PLANE;
        glm::mat4 projectionMatrix;
    public:
        Renderer();
        void init();
        void draw();
    private:
        void createProjectionMatrix();
    };

} // starlight
