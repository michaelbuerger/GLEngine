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

#include <memory>
#include <string>
#include <iostream>
#include <fstream>

namespace GLEngine { namespace graphics {

    void LoadOBJFile(const char* address, std::unique_ptr<GLfloat[]>& ret_data, std::unique_ptr<GLint[]>& ret_indices);
    GLuint CreateVAO(const GLfloat data[], const GLint indices[], const GLsizeiptr& dataSizeBytes, const GLsizeiptr& indicesSizeBytes, const GLuint& drawMode); // Note for GLsizeiptr args, sizeof operator on arrays are sufficient

}}

#endif