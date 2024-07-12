#pragma once

#include "engine/entities/Entity.h"

namespace game {

    class Barbarian:public starlight::Entity {
    private:
        starlight::Model model;
        glm::vec3 position{};
        glm::vec3 rotation{};
        glm::vec3 scale{};
        std::string tag;

        int health;
    public:
        int id;
        std::string getTag() override;
        int getId() const override;

        void increasePosition(glm::vec3 position) override;
        void increaseRotation(glm::vec3 rotation) override;

        //getters
        starlight::Model getModel() override;
        glm::vec3 getPosition() override;
        glm::vec3 getRotation() override;
        glm::vec3 getScale() override;

        //setters
        void setModel(starlight::Model &model) override;
        void setPosition(glm::vec3 position) override;
        void setRotation(glm::vec3 rotation) override;
        void setScale(glm::vec3 scale) override;
        void setTag(std::string tag) override;
        void setId(int id) override;
        //operator overloading
        bool operator==(const Entity &other) const override;

        Barbarian()=default;
        Barbarian(starlight::Model model,glm::vec3 position,glm::vec3 rotation,glm::vec3 scale,std::string tag);
    };

} // starlight

