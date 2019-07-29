// http://paulbourke.net/dataformats/obj/
// https://en.wikipedia.org/wiki/Wavefront_.obj_file
// TODO: Look into whether or not it makes sense to hold references to all VAOs and VBOs and destroy them at end of program
// Note: Currently nothing handles destroying/freeing VAOs and VBOs right now, and there doesn't seem to be any issue (even with valgrind)

#ifndef GLE_MODEL_HANDLER_HPP
#define GLE_MODEL_HANDLER_HPP

#include "GLEngine/graphics/graphics.hpp"
#include "GLEngine/defines.hpp"
#include "GLEngine/exceptions.hpp"
#include "GLEngine/io/io.hpp"
#include "GLEngine/graphics/Model.hpp"

#include <memory>
#include <string>
#include <iostream>
#include <fstream>

namespace GLEngine
{
GLuint CreateVAO(const GLfloat data[], const GLuint indices[], const GLsizeiptr &dataSizeBytes, const GLsizeiptr &indicesSizeBytes); // Note for GLsizeiptr args, sizeof operator on arrays are sufficient
GLuint CreateVAO_MultiVBO(const GLfloat vertices[], const GLfloat texcoords[], const GLfloat normals[], const GLuint indices[], const GLuint &vertexCount);

Model CreateModelFromVBOFile(const char *address, std::shared_ptr<Texture> texture);
} // namespace GLEngine

#endif