//
// Created by Msi on 10/25/2023.
//

#pragma once

#include <string>
#include "models/Model.h"
#include "vec3.hpp"

namespace starlight {

    class Entity {
    private:
        Model model;
    public:
        glm::vec3 position{};
        glm::vec3 rotation{};
        glm::vec3 scale;
        std::string tag;
        Entity(Model &model,glm::vec3 position,glm::vec3 rotation, glm::vec3 scale,std::string tag);
        void increasePosition(glm::vec3 position);
        void increaseRotation(glm::vec3 rotation);

        //getters
        Model getModel();
        glm::vec3 getPosition();
        glm::vec3 getRotation();
        glm::vec3 getScale();
        std::string getTag();
        //setters
        void setModel(Model &model);
        void setPosition(glm::vec3 position);
        void setRotation(glm::vec3 rotation);
        void setScale(glm::vec3 scale);
        void setTag(std::string tag);

        Entity();
    };

} // starlight

