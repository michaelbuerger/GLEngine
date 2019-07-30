// http://paulbourke.net/dataformats/obj/
// https://en.wikipedia.org/wiki/Wavefront_.obj_file

/* Figure out way to generate texcoords and normals */

#include "GLEngine/graphics/ModelHandler.hpp"
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

// TODO: See if this function works.
// Convert to use of vertexCount from sizeBytes
// Convert to using smart pointers
GLuint CreateVAO(const GLfloat data[], const GLuint indices[], const GLsizeiptr &dataSizeBytes, const GLsizeiptr &indicesSizeBytes)
{
    GLuint vao, vbo, elementBuffer;

    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &elementBuffer);

    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBuffer);

    glBufferData(GL_ARRAY_BUFFER, dataSizeBytes, data, GL_STATIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesSizeBytes, indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void *)0);                     // vertices
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void *)(3 * sizeof(GLfloat))); // texcoords
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void *)(5 * sizeof(GLfloat))); // normals

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);

    glBindVertexArray(0);

    return vao;
}

GLuint CreateVAO_MultiVBO(const GLfloat vertices[], const GLfloat texcoords[], const GLfloat normals[], const GLuint indices[], const GLuint &vertexCount)
{
    GLuint vao, verticesVbo, texcoordsVbo, normalsVbo, elementBuffer;

    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &verticesVbo);
    glGenBuffers(1, &texcoordsVbo);
    glGenBuffers(1, &normalsVbo);
    glGenBuffers(1, &elementBuffer);

    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, verticesVbo);
    glBufferData(GL_ARRAY_BUFFER, vertexCount * sizeof(GLfloat) * 3, vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void *)0); // vertices

    glBindBuffer(GL_ARRAY_BUFFER, texcoordsVbo);
    glBufferData(GL_ARRAY_BUFFER, vertexCount * sizeof(GLfloat) * 2, texcoords, GL_STATIC_DRAW);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void *)0); // texcoords

    glBindBuffer(GL_ARRAY_BUFFER, normalsVbo);
    glBufferData(GL_ARRAY_BUFFER, vertexCount * sizeof(GLfloat) * 3, normals, GL_STATIC_DRAW);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (void *)0); // normals

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, vertexCount * sizeof(GLuint), indices, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);

    glBindVertexArray(0);

    return vao;
}

Model CreateModelFromVBOFile(const char *address, std::shared_ptr<Texture> texture)
{

    std::unique_ptr<GLfloat[]> vertices;
    std::unique_ptr<GLfloat[]> texcoords;
    std::unique_ptr<GLfloat[]> normals;
    uint vertexCount;

    FILE *file = CPPML::OpenFile(address);
    CPPML::LoadOBJFile(file, vertices, texcoords, normals, vertexCount);

    // TODO: Create way for model to know if its indexed or not
    // TODO: Create renderer that can take this data in and render without elements when applicable

    GLuint indices[vertexCount];
    for (size_t i = 0; i < vertexCount; i++)
    {
        indices[i] = i;
    }

    GLuint vao = CreateVAO_MultiVBO(vertices.get(), texcoords.get(), normals.get(), indices, vertexCount); // Look into better way of doing this, right now these unique ptrs don't get freed ever because of .get

    Model model = Model(vao, vertexCount, texture);

    return model;
}

} // namespace GLEngine