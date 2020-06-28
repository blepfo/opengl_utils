#include <iostream>
#include <sstream>
#include <vector>


#include<GL/glew.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_inverse.hpp>

#include "GlUtils/Camera.hpp"

#include "SceneRenderer/Objects.hpp"

namespace SceneRenderer {

const std::string SceneRenderer::StaticMaterialObject::FILE_PATH = __FILE__;
const std::string SceneRenderer::StaticMaterialObject::DIR_PATH = FILE_PATH.substr(0, FILE_PATH.rfind("/"));
// StaticMaterialObject uses predefined shaders for Blinn-Phong shading
const std::string SceneRenderer::StaticMaterialObject::VERTEX_SHADER_PATH = DIR_PATH + "/mvp.vs";
const std::string SceneRenderer::StaticMaterialObject::FRAGMENT_SHADER_PATH = DIR_PATH + "/static_material_object.fs";

GlUtils::Shader SceneRenderer::StaticMaterialObject::staticShader = GlUtils::Shader(
    SceneRenderer::StaticMaterialObject::VERTEX_SHADER_PATH.c_str(), 
    SceneRenderer::StaticMaterialObject::FRAGMENT_SHADER_PATH.c_str(), 
    true
);

bool SceneRenderer::StaticMaterialObject::shaderInit = false;

void StaticMaterialObject::initShader() {
    if (!::SceneRenderer::StaticMaterialObject::shaderInit) {
        std::cout << "StaticMaterialObject::initShader - Init static Shader" << std::endl;
        ::SceneRenderer::StaticMaterialObject::staticShader.initialize();
        ::SceneRenderer::StaticMaterialObject::shaderInit = true;
    }
}

/**
 * Init normals for cube using cross products
 * len(vertices) == numVertices * 3
 * TODO - possibly delet
 */
float* StaticMaterialObject::staticTriangleNormals(
    const float vertices[], 
    const unsigned int idxs[],
    const int numVertices,
    const int numIdxs
) {
    std::cout << "StaticMaterialObject::staticTriangleNormals - Init normals" << std::endl;
    float* normals = new float[numVertices * 3];
    // Assume that idxs specify triangles 
    for (int idxNum = 0; idxNum < numIdxs; idxNum += 3) {
        // A
        int AIdx = 3 * idxs[idxNum];
        float Ax = vertices[AIdx];
        float Ay = vertices[AIdx + 1];
        float Az = vertices[AIdx + 2];
        // B
        int BIdx = 3 * idxs[idxNum + 1];
        float Bx = vertices[BIdx];
        float By = vertices[BIdx + 1];
        float Bz = vertices[BIdx + 2];
        // C
        int CIdx = 3 * idxs[idxNum + 2];
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

    /*
    for (int vertexNum = 0; vertexNum < numVertices; vertexNum++) {
        std::cout << "NORMAL FOR VERTEX " << vertexNum << std::endl;
        int idx = vertexNum * 3;
        std::cout << "(" << normals[idx] << ", " << normals[idx+1] << ", " << normals[idx+2] << ")\n";
    }
    */
    return normals;
}


void StaticMaterialObject::activateShader(
    const std::vector<::SceneRenderer::SimpleLight*>& lights,
    ::GlUtils::Camera* camera
) const {
    GlUtils::Shader* shader = &::SceneRenderer::StaticMaterialObject::staticShader;
    shader->activate();
    // Set material uniforma
    ::SceneRenderer::StaticMaterial* material = this->material;
    shader->setVec3("material.diffuse", material->diffuse);
    shader->setVec3("material.specular", material->specular);
    shader->setVec3("material.ambient", material->ambient);
    shader->setVec3("material.emission", material->emission);
    shader->setFloat("material.shiny", material->shiny);
    // Model View Projection
    const glm::mat4 view = camera->getView();
    const glm::mat4 modelView = view * this->model;
    const glm::mat4 projection = camera->getProjection();
    const glm::mat3 normalMatrix = glm::inverseTranspose(glm::mat3(modelView));
    shader->setMat4("modelView", modelView);
    shader->setMat4("modelViewProjection", projection * modelView);
    shader->setMat3("normalMatrix", normalMatrix);
    shader->setMat4("view", view);
    // Lighting uniforms
    const int numLights = lights.size();
    shader->setInt("numLights", numLights);
    for (int i = 0; i < numLights; i++) {
        ::SceneRenderer::SimpleLight* light = lights[i];
        std::stringstream uniformNameStream;
        uniformNameStream << "lights[" << i << "]";
        std::string uniformNameBase = uniformNameStream.str();
        shader->setVec3(uniformNameBase + ".origin", light->origin);
        shader->setVec3(uniformNameBase + ".diffuse", light->diffuse);
        shader->setVec3(uniformNameBase + ".specular", light->specular);
        shader->setVec3(uniformNameBase + ".ambient", light->ambient);
        shader->setBool(uniformNameBase + ".isPoint", light->isPoint);
    }
}


void SimpleCube::initialize() {
    // Create OpenGL buffers
    glGenVertexArrays(1, &this->vao);
    glGenBuffers(1, &this->vbo);
    // Bind buffers
    glBindVertexArray(this->vao);
    glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
    // Load vertices
    constexpr int numVboElements = ::SceneRenderer::SimpleCube::cubeVboSize;
    glBufferData(
        GL_ARRAY_BUFFER,
        numVboElements * 6 * sizeof(float),
        ::SceneRenderer::SimpleCube::cubeVboContents,
        GL_STATIC_DRAW
    );
    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6*sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // Normals attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6*sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
}


void SimpleCube::render(
    const std::vector<::SceneRenderer::SimpleLight*>& lights,
    GlUtils::Camera* camera
) const {
    // StaticMaterialObject activateShader binds material + light + model uniforms
    this->activateShader(lights, camera);
    glBindVertexArray(this->vao);
    glDrawArrays(GL_TRIANGLES, 0, ::SceneRenderer::SimpleCube::cubeVboSize);
    // Unbind vao to avoid errors
    glBindVertexArray(0);
}


} // namespace SceneRenderer
