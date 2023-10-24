//
// Created by Msi on 10/24/2023.
//

#include <iostream>
#include "Loader.h"
#include "glad.h"
#include "stb_image.h"

namespace starlight {
    unsigned int Loader::createVao() {
        unsigned int vaoId;
        glGenVertexArrays(1,&vaoId);
        vaos.push_back(vaoId);
        glBindVertexArray(vaoId);
        return vaoId;
    }

    void Loader::storeDataInAttributeList(int coordinateSize, int attributeNumber,std::vector<float> data) {
        unsigned int vboId;
        glGenBuffers(1,&vboId);
        vbos.push_back(vboId);
        glBindBuffer(GL_ARRAY_BUFFER,vboId);
        glBufferData(GL_ARRAY_BUFFER,data.size()*sizeof(float),data.data(),GL_STATIC_DRAW);
        glVertexAttribPointer(attributeNumber,coordinateSize,GL_FLOAT,GL_FALSE,0, nullptr);
        glBindBuffer(GL_ARRAY_BUFFER,0);
    }

    void Loader::unbindVao() {
        glBindVertexArray(0);
    }

    void Loader::bindIndicesBuffer(std::vector<int> indices) {
        unsigned int vboId;
        glGenBuffers(1,&vboId);
        vbos.push_back(vboId);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,vboId);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER,indices.size()*sizeof(int),indices.data(),GL_STATIC_DRAW);
    }

    unsigned int Loader::loadTexture(std::string filename) {
        unsigned int textureId;
        glGenTextures(1,&textureId);
        glBindTexture(GL_TEXTURE_2D,textureId);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        int width,height,nrChannels;
        unsigned char* data = stbi_load(filename.c_str(), &width, &height, &nrChannels, 0);
        if (data) {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
        }
        else {
            std::cout << "Failed to load texture\n";
        }

        textures.push_back(textureId);
        stbi_image_free(data);
        return textureId;
    }

    RawModel Loader::loadToVao(std::vector<float> positions, std::vector<int> indices, std::vector<float> textureCoords) {
        unsigned int vaoId=createVao();
        bindIndicesBuffer(indices);
        storeDataInAttributeList(3,0,positions);
        storeDataInAttributeList(2,1,textureCoords);
        unbindVao();
        return {vaoId,indices.size()};
    }

    Loader::~Loader() {
        for(auto vao:vaos){
            glDeleteVertexArrays(1,&vao);
        }
        for(auto vbo:vbos){
            glDeleteVertexArrays(1,&vbo);
        }
        for(auto texture:textures){
            glDeleteTextures(1,&texture);
        }
    }
} // starlight