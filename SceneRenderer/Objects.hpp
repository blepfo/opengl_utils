#pragma once

#include <array>
#include <cmath>
#include <string>
#include <sstream>
#include <vector>

#include <glm/glm.hpp>

#include "GlUtils/Camera.hpp"
#include "GlUtils/Shader.hpp"

#include "SceneRenderer/Lights.hpp"
#include "SceneRenderer/Materials.hpp"


namespace SceneRenderer {

class StaticMaterialObject { 
    private:
        // Get paths for shader source files
        const static std::string FILE_PATH;
        const static std::string DIR_PATH;
        // StaticMaterialObject uses predefined shaders for Blinn-Phong shading
        const static std::string VERTEX_SHADER_PATH;
        const static std::string FRAGMENT_SHADER_PATH;
        // Manually initialize shader in initialize() usint initShader()
        // So we can defer shader creation until OpenGL context is setup
        static bool shaderInit;

    public:
        // Set up e.g. VAO, textures
        virtual void initialize() = 0;
        // activateShader, Bind VAO, do glDraw*
        virtual void render(
            const std::vector<::SceneRenderer::SimpleLight*>& lights, 
            GlUtils::Camera* camera
        ) const = 0;

        virtual std::string toString() const = 0;

        // Init shader at runtime after OpenGL context is created
        static GlUtils::Shader staticShader; 

        static void initShader(); 

        void activateShader(
            const std::vector<::SceneRenderer::SimpleLight*>& lights, 
            GlUtils::Camera* camera
        ) const;

        static float* staticTriangleNormals(
            const float vertices[], 
            const unsigned int idxs[],
            const int numIdxs,
            const int numVertices
        );

        StaticMaterialObject(
            ::SceneRenderer::StaticMaterial* material
        ) : material(material), model(glm::mat4(1.0f)) {}

        StaticMaterialObject(
            ::SceneRenderer::StaticMaterial* material,
            glm::mat4 model
        ) : material(material), model(model) {}

    protected:
        ::SceneRenderer::StaticMaterial* material;
        glm::mat4 model;
};


class SimpleCube : public StaticMaterialObject {
    public:
        // 24 = 2 triangles for 6 faces
        static constexpr int cubeVboSize = 36;
        static constexpr float cubeVboContents[::SceneRenderer::SimpleCube::cubeVboSize * 6] = {
			// positions          // normals
            // Back
			-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
			 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
			 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
			 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
			-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
			-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
            // Front
			-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
			 0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
			 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
			 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
			-0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
			-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
            // Left
			-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
			-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
			-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
			-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
			-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
			-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
            // Right
			 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
			 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
			 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
			 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
			 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
			 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
            // Bottom
			-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
			 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
			 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
			 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
			-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
			-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
            // Top
			-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
			 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
			 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
			 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
			-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
			-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
        };



        // SceneRenderer::SceneObject overrides
        void initialize() override; 

        void render(
            const std::vector<::SceneRenderer::SimpleLight*>& lights,
            GlUtils::Camera* camera
        ) const override;

        std::string toString() const override {
            return "SceneRenderer::SimpleCube";
        }

        SimpleCube(::SceneRenderer::StaticMaterial* material)
            : StaticMaterialObject(material) {}

        SimpleCube(::SceneRenderer::StaticMaterial* material, glm::mat4 model)
            : StaticMaterialObject(material, model) {}

    protected:
        unsigned int vao; 
        unsigned int vbo;
        unsigned int ebo;

};

} // namespace GlUtils
