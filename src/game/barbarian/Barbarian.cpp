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
        this->scale=scale;
    }

    void Barbarian::setTag(std::string tag) {
        this->tag=tag;
    }

    void Barbarian::setId(int id) {
        this->id=id;
    }

    bool Barbarian::operator==(const starlight::IEntity &other) const {
        return this->id==other.getId();
    }

    glm::vec3 Barbarian::getScale() {
        return this->scale;
    }

    glm::vec3 Barbarian::getRotation() {
        return this->rotation;
    }

    glm::vec3 Barbarian::getPosition() {
        return this->position;
    }

    starlight::Model Barbarian::getModel() {
        return this->model;
    }

    int Barbarian::getId() const {
        return this->id;
    }

    std::string Barbarian::getTag() {
        return this->tag;
    }

    void Barbarian::increaseRotation(glm::vec3 rotation) {

    }

    void Barbarian::increasePosition(glm::vec3 position) {

    }

    Barbarian::Barbarian(starlight::Model model, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale,
                         std::string tag) {
        this->model=model;
        this->position=position;
        this->rotation=rotation;
        this->scale=scale;
        this->tag=tag;

    }


} // starlight