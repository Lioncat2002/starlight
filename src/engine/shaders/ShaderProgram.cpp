//
// Created by Msi on 10/25/2023.
//

#include <fstream>
#include <iostream>
#include "ShaderProgram.h"
#include "glad.h"
#include "detail/type_mat4x4.hpp"
#include "gtc/type_ptr.hpp"

namespace starlight {
    ShaderProgram::ShaderProgram(std::string VERTEX_FILE, std::string FRAGMENT_FILE) {
        vertexShaderId= loadShader(std::move(VERTEX_FILE),GL_VERTEX_SHADER);
        fragmentShaderId= loadShader(std::move(FRAGMENT_FILE),GL_FRAGMENT_SHADER);
        programId=glCreateProgram();
        glAttachShader(programId,vertexShaderId);
        glAttachShader(programId,fragmentShaderId);
        bindAttributes();
        glLinkProgram(programId);
        glValidateProgram(programId);
        getAllUniformLocations();
    }

    int ShaderProgram::loadShader(std::string filename, int type) {
        std::ifstream file(filename);
        std::string buffer;
        std::string src="";
        if(!file.good()){
            std::cout<<"ERROR::File not found at path: "<<filename<<"\n";
            std::exit(-1);
        }
        if (file.is_open()) {
            while (file) {
                std::getline(file,buffer);
                src += buffer+'\n';
                buffer = "";
            }
            file.close();
        }
        int shaderId=glCreateShader(type);
        const char* src_str = src.c_str();

        glShaderSource(shaderId,1,&src_str, nullptr);
        glCompileShader(shaderId);

        int success;
        char infoLog[512];
        glGetShaderiv(shaderId, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(shaderId, 512, nullptr, infoLog);
            std::cout << "ERROR::SHADER::COMPILATION_FAILED\n" << infoLog;
            std::exit(-1);
        }
        return shaderId;
    }

    void ShaderProgram::start() {
        glUseProgram(programId);
    }

    void ShaderProgram::stop() {
        glUseProgram(0);
    }

    ShaderProgram::~ShaderProgram() {
        stop();
        glDetachShader(programId,vertexShaderId);
        glDetachShader(programId,fragmentShaderId);
        glDeleteShader(vertexShaderId);
        glDeleteShader(fragmentShaderId);
        glDeleteProgram(programId);
    }

    void ShaderProgram::bindAttribute(int attribute, const std::string& variable) const {
        glBindAttribLocation(programId,attribute,variable.c_str());
    }

    void ShaderProgram::bindAttributes() {

    }

    int ShaderProgram::getUniformLocation(const std::string& uniformName) const {
        return glGetUniformLocation(programId,uniformName.c_str());
    }

    void ShaderProgram::getAllUniformLocations() {

    }

    void ShaderProgram::loadFloat(int location, float value) {
        glUniform1f(location,value);
    }

    void ShaderProgram::loadVector(int location, glm::vec3 vector) {
        glUniform3f(location,vector.x,vector.y,vector.z);
    }

    void ShaderProgram::loadMatrix(int location, glm::mat4 matrix) {
        glUniformMatrix4fv(location,1,false,glm::value_ptr(matrix));
    }

    ShaderProgram::ShaderProgram() {

    }
} // starlight