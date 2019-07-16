// http://paulbourke.net/dataformats/obj/
// https://en.wikipedia.org/wiki/Wavefront_.obj_file
// TODO: Look into whether or not it makes sense to hold references to all VAOs and VBOs and destroy them at end of program
// Note: Currently nothing handles destroying/freeing VAOs and VBOs right now, and there doesn't seem to be any issue (even with valgrind)

#ifndef MODEL_HANDLER_HPP
#define MODEL_HANDLER_HPP

#include "GLEngine/graphics/graphics.hpp"
#include "GLEngine/defines.hpp"
#include "GLEngine/exceptions.hpp"
#include "GLEngine/io/io.hpp"
#include "GLEngine/graphics/Model.hpp"

#include <memory>
#include <string>
#include <iostream>
#include <fstream>

namespace GLEngine { namespace graphics {

    bool LoadOBJFile(const char* address, std::unique_ptr<GLfloat[]>& ret_data, std::unique_ptr<GLuint[]>& ret_indices, GLuint& ret_vertexCount, GLsizeiptr& ret_dataSize, GLsizeiptr& ret_indicesSize);
    GLuint CreateVAO(const GLfloat data[], const GLuint indices[], const GLsizeiptr& dataSizeBytes, const GLsizeiptr& indicesSizeBytes); // Note for GLsizeiptr args, sizeof operator on arrays are sufficient
    Model CreateModelFromOBJ(const char* address, const std::shared_ptr<Texture>& texture);
}}

#endif