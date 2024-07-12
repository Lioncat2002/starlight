#pragma once
#include <vector>
#include "engine/entities/Entity.h"

namespace starlight {

    class World {
    public:
        static std::vector<Entity*> entities;
    };

} // starlight
