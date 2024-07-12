//
// Created by gamed on 12-07-2024.
//

#include "BaseLevel.h"

namespace game {
    void BaseLevel::setModel(starlight::Model &model) {
        this->model=model;
    }

    void BaseLevel::setPosition(glm::vec3 position) {
        this->position=position;
    }

    void BaseLevel::setRotation(glm::vec3 rotation) {
        this->rotation=rotation;
    }

    void BaseLevel::setScale(glm::vec3 scale) {
        this->scale=scale;
    }

    void BaseLevel::setTag(std::string tag) {
        this->tag=tag;
    }

    void BaseLevel::setId(int id) {
        this->id=id;
    }

    bool BaseLevel::operator==(const starlight::IEntity &other) const {
        return this->id==other.getId();
    }

    glm::vec3 BaseLevel::getScale() {
        return this->scale;
    }

    glm::vec3 BaseLevel::getRotation() {
        return this->rotation;
    }

    glm::vec3 BaseLevel::getPosition() {
        return this->position;
    }

    starlight::Model BaseLevel::getModel() {
        return this->model;
    }

    int BaseLevel::getId() const {
        return this->id;
    }

    std::string BaseLevel::getTag() {
        return this->tag;
    }

    void BaseLevel::increaseRotation(glm::vec3 rotation) {

    }

    void BaseLevel::increasePosition(glm::vec3 position) {

    }

    BaseLevel::BaseLevel(starlight::Model model, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale,
                         std::string tag) {

        this->model=model;
        this->position=position;
        this->rotation=rotation;
        this->scale=scale;
        this->tag=tag;
    }
} // game