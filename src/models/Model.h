//
// Created by Msi on 10/24/2023.
//

#pragma once

#include "RawModel.h"
#include "textures/Texture.h"

namespace starlight {

    class Model {
    private:
        RawModel rawModel;
        Texture texture;
    public:
        Model();
        Model(RawModel &model,Texture &texture);
        RawModel getRawModel();
        Texture getTexture();
    };

} // starlight
