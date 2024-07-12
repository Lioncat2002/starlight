#pragma once
#include <vector>
#include "engine/entities/IEntity.h"

namespace starlight {

    class World {
    public:
        static std::vector<IEntity*> entities;
    };

} // starlight
