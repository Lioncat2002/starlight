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
        RawModel loadToVao(std::vector<float> positions,std::vector<int> indices,std::vector<float> textureCoords,std::vector<float> normals);
        RawModel loadModelFromFile(std::string path);
        ~Loader();
    private:
        unsigned int createVao();
        void bindIndicesBuffer(std::vector<int> indices);
        void storeDataInAttributeList(int coordinateSize,int attributeNumber,std::vector<float> data);
        void LoadModel(std::string &path,std::vector<float> &vertices,std::vector<float> &textures,std::vector<float> &normals,std::vector<int> &indices);
        void unbindVao();
    };

} // starlight
