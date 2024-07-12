//
// Created by Msi on 10/25/2023.
//

#pragma once

#include <string>
#include "engine/models/Model.h"
#include "vec3.hpp"
#include <unordered_map>
#include <memory>

namespace starlight {

    class Entity {
    private:
    public:
        virtual std::string getTag()=0;
        virtual int getId() const=0;
        //Entity(Model &model,glm::vec3 position,glm::vec3 rotation, glm::vec3 scale,std::string tag);
        virtual void increasePosition(glm::vec3 position)=0;
        virtual void increaseRotation(glm::vec3 rotation)=0;

        //getters
        virtual Model getModel()=0;
        virtual glm::vec3 getPosition()=0;
        virtual glm::vec3 getRotation()=0;
        virtual glm::vec3 getScale()=0;
        //setters
        virtual void setModel(Model &model)=0;
        virtual void setPosition(glm::vec3 position)=0;
        virtual void setRotation(glm::vec3 rotation)=0;
        virtual void setScale(glm::vec3 scale)=0;
        virtual void setTag(std::string tag)=0;
        virtual void setId(int id)=0;
        //operator overloading
        virtual bool operator==(const Entity& other) const=0;
    };

} // starlight

