// http://paulbourke.net/dataformats/obj/
// https://en.wikipedia.org/wiki/Wavefront_.obj_file

#ifndef GLE_MODEL_LOADING_HPP
#define GLE_MODEL_LOADING_HPP

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

Model CreateModelFromOBJFile(const char *address, std::shared_ptr<Texture> texture);
} // namespace GLEngine

#endif