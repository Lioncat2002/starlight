//
// Created by Msi on 10/24/2023.
//

#pragma once
namespace starlight {

    class Texture {
    private:
        unsigned int textureId;
    public:
        Texture();
        explicit Texture(unsigned int textureId);
        unsigned int getId();
    };

} // starlight

