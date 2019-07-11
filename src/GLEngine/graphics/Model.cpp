#include "GLEngine/graphics/Model.hpp"

#include "GLEngine/defines.hpp"
#include "GLEngine/graphics/graphics.hpp"

namespace GLEngine { namespace graphics {
    
    GLfloat square_vertices_texcoords[]
    {
        1.0f, 1.0f, 0.0f,    1.0f, 1.0f, // top-right
        1.0f, -1.0f, 0.0f,   1.0f, 0.0f, // bottom-right
        -1.0f, 1.0f, 0.0f,   0.0f, 1.0f, // top-left
        -1.0f, -1.0f, 0.0f,  0.0f, 0.0f // bottom-left
    };

    Model::Model()
    {

    }
    /* Create model with combined data array (vertices, texcoords, and normals) per-vertex */
    Model::Model(const GLfloat* data, const GLfloat* indices, const bool& shouldUseTexcoords, const bool& shouldUseNormals) // Assumes use of heap allocated pointer
    {

    }
    Model::Model(const GLfloat* vertices, const GLfloat* texcoords, const GLfloat* normals, const GLfloat* indices) // Assumes use of heap allocated pointer
    {

    }
    Model::Model(const Model& model)
    {

    }

    /* Primitives */
    // Model Model::triangle;
    Model Model::square = square_vertices_texcoords_normals;
    // Model Model::cube;

    GLfloat *Model::GetData() const
    {

    }
    bool Model::ShouldUseTexcoords() const
    {

    }
    bool Model::ShouldUseNormals() const
    {

    }

    GLuint Model::GetVAO() const
    {
        return m_vao;
    }
    GLuint Model::GetVBO() const
    {
        return m_vbo;
    }

}}