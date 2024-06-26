#pragma once
#include "../entities/Entity.h"
#include "../renderer/Loader.h"
namespace starlight {

    class AssetServer {
    public:
        static Entity AssetLoader(Loader &loader, std::string modelPath, std::string texturePath);
    };

} // starlight

