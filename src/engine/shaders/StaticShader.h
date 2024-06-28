//
// Created by Msi on 10/25/2023.
//

#pragma once

#include "ShaderProgram.h"
#include "engine/entities/Camera.h"
#include "engine/entities/Lighting.h"

namespace starlight {

    class StaticShader: public ShaderProgram {
    private:
        int location_transformationMatrix;
        int location_projectionMatrix;
        int location_viewMatrix;
        int location_lightPosition;
        int location_lightColor;
    protected:
        void bindAttributes() override;
    public:
        void getAllUniformLocations() override;
        StaticShader(std::string VERTEX_FILE,std::string FRAGMENT_FILE);
        void loadLight(starlight::Light light);
        void loadTransformationMatrix(glm::mat4 matrix);
        void loadViewMatrix(Camera &camera);
        void loadProjectionMatrix(glm::mat4 matrix);

        StaticShader();
    };

} // starlight
