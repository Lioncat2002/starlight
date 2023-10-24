//
// Created by Msi on 10/25/2023.
//

#pragma once

#include "vec3.hpp"

namespace starlight {

    class Camera {
    private:
        glm::vec3 position;
        float pitch;
        float yaw;
        float roll;
    public:
        Camera();
        glm::vec3 getPosition();
        float getPitch();
        float getYaw();
        float getRoll();
        void move(int key);
    };

} // starlight
