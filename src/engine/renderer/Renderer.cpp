//
// Created by Msi on 10/24/2023.
//

#include "Renderer.h"
#include "glad.h"
#include "gtc/matrix_transform.hpp"
#include "engine/utils/Math.h"

namespace starlight {
    Renderer::Renderer(StaticShader &shader) {
        this->FOV=70.0f;
        this->NEAR_PLANE=0.1f;
        this->FAR_PLANE=1000.0f;
        createProjectionMatrix();
        shader.start();
        shader.loadProjectionMatrix(projectionMatrix);
        shader.stop();
    }

    void Renderer::init() {
        glClearColor(0.6784f, 0.8f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    }
    //idk why but the renderer doesn't draw if I pass a statis shader by value?
    void Renderer::draw(IEntity *entity, StaticShader &shader) {
        Model model=entity->getModel();
        RawModel rawModel=model.getRawModel();

        glBindVertexArray(rawModel.getVaoId());
        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);
        glEnableVertexAttribArray(2);
        glm::mat4 transformationMatrix=Math::createTransformationMatrix(entity->getPosition(),entity->getRotation(),entity->getScale());
        shader.loadTransformationMatrix(transformationMatrix);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D,model.getTexture().getId());
        glDrawElements(GL_TRIANGLES,rawModel.getVertexCount(),GL_UNSIGNED_INT,nullptr);
        glDisableVertexAttribArray(2);
        glDisableVertexAttribArray(1);
        glDisableVertexAttribArray(0);
        glBindVertexArray(0);
    }

    void Renderer::createProjectionMatrix() {
        float aspectRatio=1024.0f/768.0f;
        projectionMatrix=glm::perspective(glm::radians(FOV),aspectRatio,NEAR_PLANE,FAR_PLANE);
    }

    Renderer::Renderer() {

    }
} // starlight