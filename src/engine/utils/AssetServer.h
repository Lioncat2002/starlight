#pragma once
#include "engine/entities/Entity.h"
#include "engine/renderer/Loader.h"
namespace starlight {

    template <typename T> class AssetServer {
    public:
        static std::unique_ptr<T> AssetLoader(Loader &loader, std::string modelPath, std::string texturePath);
    };

    template <typename T>std::unique_ptr<T> AssetServer<T>::AssetLoader(Loader &loader, std::string modelPath, std::string texturePath) {
        auto rawModel=loader.loadModelFromFile(modelPath);
        auto texture=starlight::Texture(loader.loadTexture(texturePath));
        auto model=starlight::Model(rawModel,texture);
        auto entity=T(model, {0,0,0},{0,0,0},{1,1,1},"default");

        return std::make_unique<T>(entity);
    }

} // starlight

