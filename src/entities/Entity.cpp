//
// Created by Msi on 10/25/2023.
//

#include "Entity.h"

namespace starlight {
    Entity::Entity(Model &model, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale,std::string tag) {
        this->tag=tag;
        this->model=model;
        this->position=position;
        this->rotation=rotation;
        this->scale=scale;
    }

    void Entity::increasePosition(glm::vec3 position) {
        this->position+=position;
    }

    void Entity::increaseRotation(glm::vec3 rotation) {
        this->rotation+=rotation;
    }

    Model Entity::getModel() {
        return this->model;
    }

    glm::vec3 Entity::getPosition() {
        return this->position;
    }

    glm::vec3 Entity::getRotation() {
        return this->rotation;
    }

    glm::vec3 Entity::getScale() {
        return this->scale;
    }

    void Entity::setModel(Model &model) {
        this->model=model;
    }

    void Entity::setPosition(glm::vec3 position) {
        this->position=position;
    }

    void Entity::setRotation(glm::vec3 rotation) {
        this->rotation=rotation;
    }

    void Entity::setScale(glm::vec3 scale) {
        this->scale=scale;
    }

    Entity::Entity() {

    }
} // starlight