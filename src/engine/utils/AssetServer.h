#pragma once
#include "engine/entities/Entity.h"
#include "engine/renderer/Loader.h"
namespace starlight {

    class AssetServer {
    public:
        static Entity AssetLoader(Loader &loader, std::string modelPath, std::string texturePath);
    };

} // starlight

