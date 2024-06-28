//
// Created by gamed on 26-06-2024.
//

#include "AssetServer.h"

namespace starlight {
    Entity AssetServer::AssetLoader(Loader &loader, std::string modelPath, std::string texturePath) {
        auto rawModel=loader.loadModelFromFile(modelPath);
        auto texture=starlight::Texture(loader.loadTexture(texturePath));
        auto model=starlight::Model(rawModel,texture);
        auto entity=starlight::Entity(model, {0,0,0},{0,0,0},{1,1,1},"default");

        return entity;
    }
} // starlight