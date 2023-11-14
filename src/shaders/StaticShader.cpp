//
// Created by Msi on 10/25/2023.
//

#include "StaticShader.h"
#include "detail/type_mat4x4.hpp"
#include "entities/Camera.h"
#include "utils/Math.h"

#include <utility>

namespace starlight {
    StaticShader::StaticShader(std::string VERTEX_FILE, std::string FRAGMENT_FILE) : ShaderProgram(std::move(VERTEX_FILE),
                                                                                                   std::move(FRAGMENT_FILE)) {
        bindAttributes();
        getAllUniformLocations();
    }

    void StaticShader::bindAttributes() {
        bindAttribute(0,"position");
        bindAttribute(1,"textureCoords");
        bindAttribute(2,"normal");
        ShaderProgram::bindAttributes();
    }

    void StaticShader::getAllUniformLocations() {
        location_transformationMatrix=ShaderProgram::getUniformLocation("transformationMatrix");
        location_projectionMatrix=ShaderProgram::getUniformLocation("projectionMatrix");
        location_viewMatrix=ShaderProgram::getUniformLocation("viewMatrix");
        location_lightPosition=ShaderProgram::getUniformLocation("lightPosition");
        location_lightColor=ShaderProgram::getUniformLocation("lightColor");
        ShaderProgram::getAllUniformLocations();
    }

    void StaticShader::loadLight(starlight::Light light) {
        ShaderProgram::loadVector(location_lightPosition,light.getPosition());
        ShaderProgram::loadVector(location_lightColor,light.getColor());
    }

    void StaticShader::loadTransformationMatrix(glm::mat4 matrix) {
        ShaderProgram::loadMatrix(location_transformationMatrix,matrix);
    }

    void StaticShader::loadProjectionMatrix(glm::mat4 matrix) {
        ShaderProgram::loadMatrix(location_projectionMatrix,matrix);
    }

    void StaticShader::loadViewMatrix(Camera &camera) {
        glm::mat4 viewMatrix=Math::createViewMatrix(camera);
        ShaderProgram::loadMatrix(location_viewMatrix,viewMatrix);

    }

    StaticShader::StaticShader() {

    }
} // starlight