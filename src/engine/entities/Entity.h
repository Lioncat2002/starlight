//
// Created by Msi on 10/25/2023.
//

#pragma once

#include <string>
#include "engine/models/Model.h"
#include "vec3.hpp"
#include <unordered_map>

namespace starlight {

    class Entity {
    private:
        Model model;
    public:
        glm::vec3 position{};
        glm::vec3 rotation{};
        glm::vec3 scale;
        std::string tag;
        std::unordered_map<std::string,int> data;
        int id;

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
        bool operator==(const Entity& other) const;

        Entity();
    };

} // starlight

