#pragma once

#include "vec3.hpp"

namespace starlight {

    class Light {
    private:
        glm::vec3 position;
        glm::vec3 color;
    public:
        Light(glm::vec3 position,glm::vec3 color);
        glm::vec3 getPosition();
        glm::vec3 getColor();
        void setPosition(glm::vec3 position);
        void setColor(glm::vec3 color);

        Light();
    };

} // starlight