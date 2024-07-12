#include "ECS.h"
//a simple ECS for the game
namespace starlight {
    std::vector<std::unique_ptr<Entity>> World::entities;
} // starlight