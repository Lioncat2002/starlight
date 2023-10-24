#pragma once
#include <vector>
#include <string>
#include "models/RawModel.h"

namespace starlight {

    class Loader {
    private:
        std::vector<unsigned int> vaos;
        std::vector<unsigned int> vbos;
        std::vector<unsigned int> textures;
    public:
        unsigned int loadTexture(std::string filename);
        RawModel loadToVao(std::vector<float> positions,std::vector<int> indices,std::vector<float> textureCoords);
        ~Loader();
    private:
        unsigned int createVao();
        void bindIndicesBuffer(std::vector<int> indices);
        void storeDataInAttributeList(int coordinateSize,int attributeNumber,std::vector<float> data);
        void unbindVao();
    };

} // starlight
