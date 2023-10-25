#pragma once

#include "detail/type_mat.hpp"
#include "detail/type_mat4x4.hpp"
#include "shaders/StaticShader.h"
#include "entities/Entity.h"

namespace starlight {

    class Renderer {
    private:
        float FOV;
        float NEAR_PLANE;
        float FAR_PLANE;
        glm::mat4 projectionMatrix;
    public:
        Renderer(StaticShader &shader);

        void init();
        void draw(Entity &entity,StaticShader &shader);

        Renderer();

    private:
        void createProjectionMatrix();
    };

} // starlight
