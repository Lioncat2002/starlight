//
// Created by Msi on 10/24/2023.
//

#include "Texture.h"

namespace starlight {
    Texture::Texture() {

    }

    Texture::Texture(unsigned int textureId) {
        this->textureId=textureId;
    }

    unsigned int Texture::getId() {
        return this->textureId;
    }
} // starlight