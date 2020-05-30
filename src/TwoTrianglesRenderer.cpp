#include<string>

#include<GL/glew.h>
#include<GLFW/glfw3.h>

#include "../include/Shader.h"
#include "../include/SimpleRenderer.h"
#include "../include/TwoTrianglesRenderer.h"

/** 
 * Init VAO+VBO+EBO for two triangles
 */
void TwoTrianglesRenderer::initScene() {
	// Vertex data
	float vertices[] = {
		-1.0, -1.0, 0.0,
		-1.0, 1.0, 0.0,
		1.0, -1.0, 0.0,
		1.0, 1.0, 0.0,
	};
	unsigned int indices[] = {
		0, 1, 2,
		1, 3, 2
	};
	unsigned int vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	unsigned int vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*) 0);
	glEnableVertexAttribArray(0);
	unsigned int ebo;
	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	// Store for access in renderObjects()
	this->vao = vao;
	this->vbo = vbo;
	this->ebo = ebo;

    // NOTE - This won't work with windows
    std::string filePath = __FILE__;
    std::string dirPath = filePath.substr(0, filePath.rfind("/"));
    std::string vertexShaderPath = dirPath + "/" + "twotriangles.vs";
    this->shader = new Shader(
        vertexShaderPath.c_str(),
        this->fragmentShaderPath
    );
}

/** 
 * Bind VAO, assign uniforms, and draw
 */
void TwoTrianglesRenderer::renderObjects() {
    glBindVertexArray(this->vao);
    this->shader->activate();
    this->setUniforms(); 
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}
