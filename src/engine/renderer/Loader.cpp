//
// Created by Msi on 10/24/2023.
//

#include <iostream>
#include "Loader.h"
#include "glad.h"
#include "stb_image.h"
#include "assimp/mesh.h"
#include "assimp/scene.h"
#include "assimp/postprocess.h"
#include "assimp/Importer.hpp"

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
            //CHANGE to GL_RGB incase the game crashes
            //IF colors are wrong change to GL_RGBA
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
        }
        else {
            std::cout << "Failed to load texture\n";
        }

        textures.push_back(textureId);
        stbi_image_free(data);
        return textureId;
    }

    RawModel Loader::loadToVao(std::vector<float> positions, std::vector<int> indices, std::vector<float> textureCoords,std::vector<float> normals) {
        unsigned int vaoId=createVao();
        bindIndicesBuffer(indices);
        storeDataInAttributeList(3,0,positions);
        storeDataInAttributeList(2,1,textureCoords);
        storeDataInAttributeList(3,2,normals);
        unbindVao();
        return {vaoId,static_cast<unsigned int>(indices.size())};
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

    void Loader::LoadModel(std::string &path,std::vector<float> &vertices,std::vector<float> &textures,std::vector<float> &normals,std::vector<int> &indices){
        Assimp::Importer importer;
        const aiScene *scene=importer.ReadFile(path,aiProcess_Triangulate|aiProcess_FlipUVs);
        if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode){
            std::cout<<"ERROR: Assimp failed to load OBJ model: "<<importer.GetErrorString()<<std::endl;
            return;
        }


        for (unsigned int j = 0; j < scene->mNumMeshes; j++) {
            const aiMesh* mesh = scene->mMeshes[j];

            for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
                vertices.push_back(mesh->mVertices[i].x);
                vertices.push_back(mesh->mVertices[i].y);
                vertices.push_back(mesh->mVertices[i].z);

                if (mesh->HasTextureCoords(0)) {
                    textures.push_back(mesh->mTextureCoords[0][i].x);
                    textures.push_back(mesh->mTextureCoords[0][i].y);
                } else {
                    textures.push_back(0.0f);
                    textures.push_back(0.0f);
                }

                if (mesh->HasNormals()) {
                    normals.push_back(mesh->mNormals[i].x);
                    normals.push_back(mesh->mNormals[i].y);
                    normals.push_back(mesh->mNormals[i].z);
                } else {
                    normals.push_back(0.0f);
                    normals.push_back(0.0f);
                    normals.push_back(0.0f);
                }
            }

            for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
                const aiFace &face = mesh->mFaces[i];
                for (unsigned int k = 0; k < face.mNumIndices; k++) {
                    indices.push_back(face.mIndices[k]);
                }
            }
        }

    }

    RawModel Loader::loadModelFromFile(std::string path) {
        std::vector<float> vertices;
        std::vector<float> textures;
        std::vector<float> normals;
        std::vector<int> indices;

        LoadModel(path,vertices,textures,normals,indices);
        return loadToVao(vertices,indices,textures,normals);
    }
} // starlight