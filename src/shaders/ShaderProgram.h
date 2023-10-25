//
// Created by Msi on 10/25/2023.
//

#pragma once
#include <string>
#include "vec3.hpp"
#include "detail/type_mat.hpp"

namespace starlight {

    class ShaderProgram {
    private:
        int programId;
        int vertexShaderId;
        int fragmentShaderId;
    protected:
        virtual void bindAttributes();
        void bindAttribute(int attribute, const std::string& variable) const;

        //Uniform locations
        int getUniformLocation(const std::string& uniformName) const;

        virtual void getAllUniformLocations();

        //Uniform loaders
        void loadFloat(int location,float value);
        void loadVector(int location,glm::vec3 vector);
        void loadMatrix(int location,glm::mat4 matrix);
    private:
        static int loadShader(std::string filename,int type);
    public:
        ShaderProgram();
        ShaderProgram(std::string VERTEX_FILE,std::string FRAGMENT_FILE);
        ~ShaderProgram();
        void start();
        void stop();
    };

} // starlight
