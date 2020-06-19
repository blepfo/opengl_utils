#include <sstream>
#include <string>
#include <vector>

#include<GL/glew.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_inverse.hpp>

#include "GlUtils/Camera.hpp"

#include "SceneRenderer/Objects.hpp"

namespace SceneRenderer {


GlUtils::Shader StaticMaterialObject::staticMaterialObjectShader() {
    const std::string filePath = __FILE__;
    const std::string dirPath = filePath.substr(0, filePath.rfind("/"));
    // StaticMaterialObject uses predefined shaders for Blinn-Phong shading
    const std::string vertexShaderPath = dirPath + "/src/mvp.vs";
    const std::string fragmentShaderPath = dirPath + "/src/static_material_object.fs";
    return GlUtils::Shader(vertexShaderPath.c_str(), fragmentShaderPath.c_str());
}

const GlUtils::Shader StaticMaterialObject::shader = staticMaterialObjectShader();


void StaticMaterialObject::activateShader(
    const std::vector<::SceneRenderer::SimpleLight*>& lights,
    const ::GlUtils::Camera& camera
) const {
        this->shader.activate();
        // Set material uniforma
        ::SceneRenderer::StaticMaterial* material = this->material;
        this->shader.setVec3("material.diffuse", material->diffuse);
        this->shader.setVec3("material.specular", material->specular);
        this->shader.setVec3("material.ambient", material->ambient);
        this->shader.setVec3("material.emission", material->emission);
        this->shader.setFloat("material.shiny", material->shiny);
        // Model View Projection
        const glm::mat4 view = camera.getView();
        const glm::mat4 modelView = view * this->model;
        const glm::mat4 projection = camera.getProjection();
        const glm::mat3 normalMatrix = glm::inverseTranspose(modelView);
        this->shader.setMat4("modelViewProjection", projection * modelView);
        this->shader.setMat3("normalMatrix", normalMatrix);
        this->shader.setMat4("view", view);
        // Lighting uniforms
        const int numLights = lights.size();
        this->shader.setInt("numLights", numLights);
        for (int i = 0; i < numLights; i++) {
            ::SceneRenderer::SimpleLight* light = lights[i];
            std::stringstream uniformNameStream;
            uniformNameStream << "Light[" << i << "]";
            std::string uniformNameBase = uniformNameStream.str();
            this->shader.setVec3(uniformNameBase + ".origin", light->origin);
            this->shader.setVec3(uniformNameBase + ".diffuse", light->diffuse);
            this->shader.setVec3(uniformNameBase + ".specular", light->specular);
            this->shader.setVec3(uniformNameBase + ".ambient", light->ambient);
            this->shader.setBool(uniformNameBase + ".isPoint", light->isPoint);
        }
}


void SimpleCube::initialize() {
    // Create OpenGL buffers
    glGenVertexArrays(1, &this->vao);
    glGenBuffers(1, &this->vbo);
    glGenBuffers(1, &this->ebo);
    // Bind buffers
    glBindVertexArray(this->vao);
    glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->ebo);
    // Load vertices

    // TODO does sizeof work here?
    glBufferData(
        GL_ARRAY_BUFFER,
        sizeof(SimpleCube::vertices),
        SimpleCube::vertices,
        GL_STATIC_DRAW
    );
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6*sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // TODO attrib pointer for normals

    // Load indices
    glBufferData(
        GL_ELEMENT_ARRAY_BUFFER, 
        sizeof(SimpleCube::idxs), 
        SimpleCube::idxs, 
        GL_STATIC_DRAW
    );

}


void SimpleCube::render(
    const std::vector<::SceneRenderer::SimpleLight*>& lights,
    const GlUtils::Camera& camera
) const {
    // StaticMaterialObject activateShader binds material + light + model uniforms
    this->activateShader(lights, camera);
    glBindVertexArray(this->vao);
    glDrawElements(GL_TRIANGLES, sizeof(SimpleCube::idxs), GL_UNSIGNED_INT, 0);
    // Unbind vao to avoid errors
    glBindVertexArray(0);
}


} // namespace SceneRenderer
