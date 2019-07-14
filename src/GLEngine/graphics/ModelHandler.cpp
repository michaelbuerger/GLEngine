// http://paulbourke.net/dataformats/obj/
// https://en.wikipedia.org/wiki/Wavefront_.obj_file

/* Figure out way to generate texcoords and normals */

#include "GLEngine/graphics/ModelHandler.hpp"
#include "GLEngine/graphics/graphics.hpp"
#include "GLEngine/defines.hpp"
#include "GLEngine/exceptions.hpp"
#include "GLEngine/io/io.hpp"

#include <memory>
#include <string>
#include <iostream>
#include <fstream>

namespace GLEngine { namespace graphics {

    GLfloat square_vertices_texcoords_normals[]
    {
        1.0f, 1.0f, 0.0f,    1.0f, 1.0f,   0.0f, 0.0f, 1.0f, // top-right
        1.0f, -1.0f, 0.0f,   1.0f, 0.0f,   0.0f, 0.0f, 1.0f, // bottom-right
        -1.0f, 1.0f, 0.0f,   0.0f, 1.0f,   0.0f, 0.0f, 1.0f, // top-left
        -1.0f, -1.0f, 0.0f,  0.0f, 0.0f,   0.0f, 0.0f, 1.0f  // bottom-left
    };

    GLint square_indices[]
    {
        2, 1, 3, 0, 1, 2
    };

    ModelHandler::ModelHandler()
    {

    }

    void LoadOBJFile(const char* address, std::unique_ptr<GLfloat[]>& ret_vertices, std::unique_ptr<GLfloat[]>& ret_texcoords, std::unique_ptr<GLfloat[]>& ret_normals, std::unique_ptr<GLint[]>& ret_indices)
    {
        /* std::stof converts std::string to float, contained in <string>, doesn't care about spaces before and after num */
    }

    GLuint ModelHandler::CreateVAO(const GLfloat data[], const GLint indices[], const GLsizeiptr& dataSizeBytes, const GLsizeiptr& indicesSizeBytes, GLuint& drawMode)
    {
        GLuint vao, vbo, elementBuffer;

        glGenVertexArrays(1, &vao);
        glGenBuffers(1, &vbo);
        glGenBuffers(1, &elementBuffer);

        glBindVertexArray(vao);

        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBuffer);

        glBufferData(GL_ARRAY_BUFFER, dataSizeBytes, data, drawMode);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesSizeBytes, indices, drawMode);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)0);                     // vertices
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat))); // texcoords
        glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)(5 * sizeof(GLfloat))); // normals
        // TODO: Add support for data structure differing from the following: 3D vertices, 2D texcoords, 3D normals

        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);
        glEnableVertexAttribArray(2);

        glBindVertexArray(0);

        return vao;
    }

}}