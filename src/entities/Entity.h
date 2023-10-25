//
// Created by Msi on 10/25/2023.
//

#pragma once

#include "models/Model.h"
#include "vec3.hpp"

namespace starlight {

    class Entity {
    private:
        Model model;
        glm::vec3 position{};
        glm::vec3 rotation{};
        glm::vec3 scale;
    public:
        Entity(Model &model,glm::vec3 position,glm::vec3 rotation, glm::vec3 scale);
        void increasePosition(glm::vec3 position);
        void increaseRotation(glm::vec3 rotation);

        //getters
        Model getModel();
        glm::vec3 getPosition();
        glm::vec3 getRotation();
        glm::vec3 getScale();
        //setters
        void setModel(Model &model);
        void setPosition(glm::vec3 position);
        void setRotation(glm::vec3 rotation);
        void setScale(glm::vec3 scale);

        Entity();
    };

} // starlight

