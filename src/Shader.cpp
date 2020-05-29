#include<fstream>
#include<iostream>
#include<sstream>

#include<GL/glew.h>

#include<glm/glm.hpp>
#include<glm/gtc/type_ptr.hpp>

#include "../include/Shader.h"


Shader::Shader(const char* vertexPath, const char* fragmentPath) :
    _vertexPath(std::string(vertexPath)), _fragmentPath(std::string(fragmentPath))
{
    // Vertex shader
    std::string vertexSource = this->readFile(vertexPath);
    unsigned int vertexId = this->compile(vertexSource.c_str(), GL_VERTEX_SHADER);
    // Fragment shader
    std::string fragmentSource = this->readFile(fragmentPath);
    unsigned int fragmentId = this->compile(fragmentSource.c_str(), GL_FRAGMENT_SHADER);
    // Compile shaders
    this->programId = this->link(vertexId, fragmentId);
    // Delete shaders because their data is now contained in shader program
    glDeleteShader(vertexId);
    glDeleteShader(fragmentId);
}


void Shader::activate() {
    glUseProgram(this->programId);
}


void Shader::setBool(const std::string &name, bool value) {
    unsigned int uniformLocation = glGetUniformLocation(this->programId, name.c_str());
    glUniform1i(uniformLocation, (int) value);
}


void Shader::setInt(const std::string &name, int value) {
    unsigned int uniformLocation = glGetUniformLocation(this->programId, name.c_str());
    glUniform1i(uniformLocation, value);
}


void Shader::setFloat(const std::string &name, float value) {
    unsigned int uniformLocation = glGetUniformLocation(this->programId, name.c_str());
    glUniform1f(uniformLocation, value);
}

void Shader::setMat4(const std::string &name, glm::mat4 m) {
    unsigned int uniformLocation = glGetUniformLocation(this->programId, name.c_str());
    glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, glm::value_ptr(m));
}

void Shader::setVec2(const std::string &name, glm::vec2 v) {
    unsigned int uniformLocation = glGetUniformLocation(this->programId, name.c_str());
    glUniform2fv(uniformLocation, 1, glm::value_ptr(v));
}

void Shader::setVec3(const std::string &name, glm::vec3 v) {
    unsigned int uniformLocation = glGetUniformLocation(this->programId, name.c_str());
    glUniform3fv(uniformLocation, 1, glm::value_ptr(v));
}

// Return std::string instead of const char* to avoid dealing with allocs
std::string Shader::readFile(const char* path) {
    std::ifstream shaderFile;
    std::stringstream readStream;
    // Allow ifstream object to throw exceptions
    std::cout << "Read shader from " << path << std::endl;
    shaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    shaderFile.open(path);
    // Read file buffer into string stream
    readStream << shaderFile.rdbuf();
    shaderFile.close();
    std::string fileContents = readStream.str();
    return fileContents;
}


unsigned int Shader::compile(
    const char* shaderSource, 
    GLenum shaderType
) {
    std::stringstream errorStream;
    unsigned int shaderId = glCreateShader(shaderType);
    glShaderSource(shaderId, 1, &shaderSource, NULL);
    glCompileShader(shaderId);
    // Check for compile errors
    int compileSuccess;
    char infoLog[512];
    glGetShaderiv(shaderId, GL_COMPILE_STATUS, &compileSuccess);
    if (!compileSuccess) {
        glGetShaderInfoLog(shaderId, 512, NULL, infoLog);
        errorStream << "ERROR::SHADER::COMPILE\n" << infoLog << std::endl;
        throw std::runtime_error(errorStream.str());
    }
    return shaderId;
}


unsigned int Shader::link(
    unsigned int vertexId,
    unsigned int fragmentId
) {
    std::stringstream errorStream;
    unsigned int programId = glCreateProgram();
    glAttachShader(programId, vertexId);
    glAttachShader(programId, fragmentId);
    glLinkProgram(programId);
    // Check for linking errors
    int linkSuccess;
    char infoLog[512];
    glGetProgramiv(programId, GL_LINK_STATUS, &linkSuccess);
    if (!linkSuccess) {
        glGetProgramInfoLog(programId, 512, NULL, infoLog);
        errorStream << "ERROR::SHADER::PROGRAM\n" << infoLog << std::endl;
        throw std::runtime_error(errorStream.str());
    }
    return programId;
}
