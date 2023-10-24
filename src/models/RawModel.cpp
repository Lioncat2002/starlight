//
// Created by Msi on 10/24/2023.
//

#include "RawModel.h"
namespace starlight{
    RawModel::RawModel(unsigned int vaoId,unsigned int vertexCount) {
        this->vaoId=vaoId;
        this->vertexCount=vertexCount;
    }

    int RawModel::getVaoId() const {
        return this->vaoId;
    }

    int RawModel::getVertexCount() const {
        return this->vertexCount;
    }

    RawModel::RawModel() {

    }
}

