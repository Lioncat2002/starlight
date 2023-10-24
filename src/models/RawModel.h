//
// Created by Msi on 10/24/2023.
//

#pragma once
namespace starlight{
    class RawModel {
    private:
        int vaoId;
        int vertexCount;
    public:
        RawModel(int vaoId,int vertexCount);
        int getVaoId() const;
        int getVertexCount() const;
    };
}

