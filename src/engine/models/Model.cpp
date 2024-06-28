//
// Created by Msi on 10/24/2023.
//

#include "Model.h"

namespace starlight {
    Model::Model(RawModel &model, Texture &texture) {
        this->rawModel=model;
        this->texture=texture;
    }

    Model::Model() {

    }

    RawModel Model::getRawModel() {
        return rawModel;
    }

    Texture Model::getTexture() {
        return texture;
    }
} // starlight