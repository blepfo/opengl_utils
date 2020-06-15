#pragma once

#include<string>

#include<GL/glew.h>
#include <glm/glm.hpp>

namespace GlUtils {

class Shader {
    public:
        unsigned int programId;

        Shader(const char* vertexPath, const char* fragmentPath);

        void activate() const;

        // Set uniform values
        void setBool(const std::string &name, const bool value) const;
        void setInt(const std::string &name, const int value) const;
        void setFloat(const std::string &name, const float value) const;
        void setMat4(const std::string &name, const glm::mat4 m) const;
        void setVec2(const std::string &name, const glm::vec2 v) const;
        void setVec3(const std::string &name, const glm::vec3 v) const;

    private:
        const std::string _vertexPath;
        const std::string _fragmentPath;
        
        std::string readFile(const char* path) const;
        unsigned int compile(const char* shaderSource, GLenum shaderType) const;
        unsigned int link(unsigned int vertexId, unsigned int fragmentId) const;
};

} // namespace GlUtils
