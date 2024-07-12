//
// Created by gamed on 28-06-2024.
//

#include "Barbarian.h"

namespace game {

    void Barbarian::setModel(starlight::Model &model) {
        this->model=model;
    }

    void Barbarian::setPosition(glm::vec3 position) {
        this->position=position;
    }

    void Barbarian::setRotation(glm::vec3 rotation) {
        this->rotation=rotation;
    }

    void Barbarian::setScale(glm::vec3 scale) {
        return void();
    }

    void Barbarian::setTag(std::string tag) {
        return void();
    }

    bool Barbarian::operator==(const starlight::Entity &other) const {
        return false;
    }

    glm::vec3 Barbarian::getScale() {
        return glm::vec3();
    }

    glm::vec3 Barbarian::getRotation() {
        return glm::vec3();
    }

    glm::vec3 Barbarian::getPosition() {
        return glm::vec3();
    }

    starlight::Model Barbarian::getModel() {
        return starlight::Model();
    }

    int Barbarian::getId() {
        return this->id;
    }

    std::string Barbarian::getTag() {
        return this->tag;
    }

    void Barbarian::increaseRotation(glm::vec3 rotation) {

    }

    void Barbarian::increasePosition(glm::vec3 position) {

    }


} // starlight