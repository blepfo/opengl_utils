#ifndef _SHADER_H
#define _SHADER_H

#include<string>
#include<GL/glew.h>
#include <glm/glm.hpp>

class Shader {
    public:
        unsigned int programId;

        Shader(const char* vertexPath, const char* fragmentPath);
        void activate();

        // Set uniform values
        void setBool(const std::string &name, bool value);
        void setInt(const std::string &name, int value);
        void setFloat(const std::string &name, float value);
        void setMat4(const std::string &name, glm::mat4 m);
        void setVec3(const std::string &name, glm::vec3 v);

    private:
        const std::string _vertexPath;
        const std::string _fragmentPath;
        
        std::string readFile(const char* path);
        unsigned int compile(const char* shaderSource, GLenum shaderType);
        unsigned int link(unsigned int vertexId, unsigned int fragmentId);
};

#endif
