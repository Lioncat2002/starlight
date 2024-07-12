#pragma once
#include <vector>
#include "engine/entities/Entity.h"

namespace starlight {

    class World {
    public:
        static std::vector<std::unique_ptr<Entity>> entities;
    };

} // starlight
