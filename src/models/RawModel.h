//
// Created by Msi on 10/24/2023.
//

#pragma once
namespace starlight{
    class RawModel {
    private:
        unsigned int vaoId;
        unsigned int vertexCount;
    public:
        RawModel();
        RawModel(unsigned int vaoId,unsigned int vertexCount);
        int getVaoId() const;
        int getVertexCount() const;
    };
}

