//
// Created by Msi on 10/25/2023.
//

#pragma once

#include "ShaderProgram.h"

namespace starlight {

    class StaticShader: public ShaderProgram {
    private:
        int location_transformationMatrix;
        int location_projectionMatrix;
        int location_viewMatrix;
    protected:
        void bindAttributes() override;
    public:
        void getAllUniformLocations() override;
        StaticShader(std::string VERTEX_FILE,std::string FRAGMENT_FILE);
        void loadTransformationMatrix(glm::mat4 matrix);
        void loadViewMatrix();
        void loadProjectionMatrix(glm::mat4 matrix);
    };

} // starlight
