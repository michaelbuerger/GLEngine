// http://paulbourke.net/dataformats/obj/
// https://en.wikipedia.org/wiki/Wavefront_.obj_file

/* Figure out way to generate texcoords and normals */

#include "GLEngine/graphics/ModelLoading.hpp"
#include "GLEngine/graphics/graphics.hpp"
#include "GLEngine/logging/Log.hpp"
#include "GLEngine/defines.hpp"
#include "GLEngine/exceptions.hpp"
#include "GLEngine/io/io.hpp"

#include "CPPML/loading/loading.hpp"
#include "CPPML/loading/OBJ.hpp"

#include <memory>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <stdio.h>

namespace GLEngine
{

GLuint CreateVAO_MultiVBO(const GLfloat vertices[], const GLfloat texcoords[], const GLfloat normals[], const GLuint indices[], const GLuint &vertexCount, const GLuint &indicesCount)
{
    GLuint vao, verticesVbo, texcoordsVbo, normalsVbo, elementBuffer;

    glGenVertexArrays(1, &vao); // generate vertex array object (big boss)
    glGenBuffers(1, &verticesVbo); // generate vertex buffer object for vertex positions (3)
    glGenBuffers(1, &texcoordsVbo); // generate vertex buffer object for texture coordinates (2)
    glGenBuffers(1, &normalsVbo); // generate vertex buffer object for normal vectors (3)
    glGenBuffers(1, &elementBuffer); // generate vertex buffer object for indices (1)

    glBindVertexArray(vao); // bind vao/make it current

    glBindBuffer(GL_ARRAY_BUFFER, verticesVbo); // bind vertex position vbo
    glBufferData(GL_ARRAY_BUFFER, vertexCount * sizeof(GLfloat) * 3, vertices, GL_STATIC_DRAW); // copy vertex positions into data store on the GPU
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void *)0); // vertex shader variable w attribute location 0 --> vertex positions

    glBindBuffer(GL_ARRAY_BUFFER, texcoordsVbo); // bind texture coordinates vbo
    glBufferData(GL_ARRAY_BUFFER, vertexCount * sizeof(GLfloat) * 2, texcoords, GL_STATIC_DRAW); // copy texture coordinates into data store on the GPU
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void *)0); // // vertex shader variable w attribute location 0 --> texture coordinates

    glBindBuffer(GL_ARRAY_BUFFER, normalsVbo); // bind normals vbo
    glBufferData(GL_ARRAY_BUFFER, vertexCount * sizeof(GLfloat) * 3, normals, GL_STATIC_DRAW); // copy normals into data store on the GPU
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (void *)0); // // vertex shader variable w attribute location 0 --> normals

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBuffer); // bind indices vbo
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesCount * sizeof(GLuint), indices, GL_STATIC_DRAW); // copy indices into data store on the GPU

    // enable vertex attributes (to be sent to and used in the vertex shader)
    glEnableVertexAttribArray(0); // vertex positions
    glEnableVertexAttribArray(1); // texture coordinates
    glEnableVertexAttribArray(2); // normals

    glBindVertexArray(0); // unbind vao

    return vao;
}

Model CreateModelFromOBJFile(const char *address)
{
    std::vector<GLfloat> positions, textureCoords, normals;
    std::vector<GLuint> indices;

    FILE *file = CPPML::OpenFile(address);
    CPPML::LoadOBJFile(file, positions, textureCoords, normals, indices);
    GLuint vertexCount = positions.size()/3;
    GLuint indicesCount = indices.size();

    GLuint vao = CreateVAO_MultiVBO(positions.data(), textureCoords.data(), normals.data(), indices.data(), vertexCount, indicesCount);

    Model model = Model(vao, indicesCount);

    return model;
}

} // namespace GLEngine