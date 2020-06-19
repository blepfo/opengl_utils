#pragma once

#include <array>
#include <cmath>
#include <vector>

#include "GlUtils/Camera.hpp"
#include "GlUtils/Shader.hpp"

#include "SceneRenderer/Lights.hpp"
#include "SceneRenderer/Materials.hpp"


namespace SceneRenderer {

/**
 * Assume 3 | numIdxs and that normals.size == (vertices.size / 3)
 */
template<int numIdxs, int numVertices>
constexpr std::array<float, numVertices> staticTriangleNormals(
    float vertices[numVertices*3], 
    float idxs[numIdxs]
) {
    // Assume that idxs specify triangles 
    static_assert(numIdxs % 3 == 0);
    std::array<float, numVertices> normals = { 0.0f };
    for (int i = 0; i < numIdxs; i+=3) {
        // A
        int AIdx = 3 * idxs[i];
        float Ax = vertices[AIdx];
        float Ay = vertices[AIdx + 1];
        float Az = vertices[AIdx + 2];
        // B
        int BIdx = 3 * idxs[i + 1];
        float Bx = vertices[BIdx];
        float By = vertices[BIdx + 1];
        float Bz = vertices[BIdx + 2];
        // C
        int CIdx = 3 * idxs[i + 2];
        float Cx = vertices[CIdx];
        float Cy = vertices[CIdx + 1];
        float Cz = vertices[CIdx + 2];
        // B-A
        float BmAx = Bx - Ax;
        float BmAy = By - Ay;
        float BmAz = Bz - Az;
        // C-A
        float CmAx = Cx - Ax;
        float CmAy = Cy - Ay;
        float CmAz = Cz - Az;
        // Cross product
        // TODO - normalize?
        float crossX = (BmAy * CmAz) - (BmAz * CmAy);
        float crossY = (BmAz * CmAx) - (BmAx * CmAz);
        float crossZ = (BmAx * CmAy) - (BmAy * CmAx);
        // Accumulate normal values
        // A
        normals[AIdx] += crossX;
        normals[AIdx + 1] += crossY;
        normals[AIdx + 2] += crossZ;
        // B
        normals[BIdx] += crossX;
        normals[BIdx + 1] += crossY;
        normals[BIdx + 2] += crossZ;
        // C
        normals[CIdx] += crossX;
        normals[CIdx + 1] += crossY;
        normals[CIdx + 2] += crossZ;
    }
    return normals;
}


class StaticMaterialObject { 
    public:
        // Set up e.g. VAO, textures
        virtual void initialize() = 0;
        // activateShader, Bind VAO, do glDraw*
        virtual void render(
            const std::vector<::SceneRenderer::SimpleLight*>& lights, 
            const GlUtils::Camera&cmaera
        ) const = 0;

        void activateShader(
            const std::vector<::SceneRenderer::SimpleLight*>& lights, 
            const GlUtils::Camera& camera
        ) const; 

        static GlUtils::Shader staticMaterialObjectShader();

        StaticMaterialObject(
            ::SceneRenderer::StaticMaterial* material
        ) : material(material), 
            model(glm::mat4(1.0f)) {}

        StaticMaterialObject(
            ::SceneRenderer::StaticMaterial* material,
            glm::mat4 model
        ) : material(material), model(model) {}

    protected:
        static const GlUtils::Shader shader;
        ::SceneRenderer::StaticMaterial* material;
        glm::mat4 model;
};


class SimpleCube : public StaticMaterialObject {
    public:
        static constexpr int numCubeVertices = 8;
        static constexpr int numCubeIdxs = 36;
        static constexpr float vertices[numCubeVertices * 3] = {
            -0.5f, 0.5f, -0.5f,     // t-bl
            -0.5f, 0.5f, 0.5f,      // t-fl
            0.5f, 0.5f, 0.5f,       // t-fr
            0.5f, 0.5f, -0.5f,       // t-br
            -0.5f, -0.5f, -0.5f,     // b-bl
            -0.5f, -0.5f, 0.5f,      // b-fl
            0.5f, -0.5f, 0.5f,       // b-fr
            0.5f, -0.5f, -0.5f,       // b-br
        };
        static constexpr unsigned int idxs[numCubeIdxs] {
            // Top
            0, 1, 2,
            2, 3, 0,
            // Left
            0, 1, 5,
            5, 4, 0,
            // Front 
            1, 5, 2,
            6, 2, 1,
            // Right
            3, 2, 6,
            7, 3, 2,
            // Back
            3, 0, 4,
            4, 7, 3,
            // Bottom
            4, 5, 6,
            6, 7, 4
        };

        static constexpr std::array<float, numCubeVertices> normals = 
            staticTriangleNormals<SimpleCube::numCubeIdxs, SimpleCube::numCubeVertices>(
                SimpleCube::vertices, 
                SimpleCube::idxs
            );
        
        // SceneRenderer::SceneObject overrides
        void initialize() override; 

        void render(
            const std::vector<::SceneRenderer::SimpleLight*>& lights,
            const GlUtils::Camera& camera
        ) const override;

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
