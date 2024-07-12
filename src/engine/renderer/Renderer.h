#pragma once

#include "detail/type_mat.hpp"
#include "detail/type_mat4x4.hpp"
#include "engine/shaders/StaticShader.h"
#include "engine/entities/IEntity.h"

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
        void draw(IEntity *entity, StaticShader &shader);

        Renderer();

    private:
        void createProjectionMatrix();
    };

} // starlight
