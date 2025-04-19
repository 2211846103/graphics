#pragma once

#include <resource_management/shader.hpp>

#ifdef ENGINE_COMPILE_OPENGL
#include <glad/glad.h>
#endif

using namespace engine::resource_management;

#ifdef ENGINE_COMPILE_OPENGL
unsigned int VAO;

OpenGLShader shader(
    std::make_shared<File>("path/to/vertex_shader.vert"),
    std::make_shared<File>("path/to/fragment_shader.frag")
);

void openGLTriangleTest() {
    float vertices[] = {
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.0f,  0.5f, 0.0f
    };
    
    glGenVertexArrays(1, &VAO);
    
    unsigned int VBO;
    glGenBuffers(1, &VBO);
    
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    
    shader.useShader();
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

}
#endif