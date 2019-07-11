#include "GLEngine/graphics/Model.hpp"

#include "GLEngine/defines.hpp"
#include "GLEngine/graphics/graphics.hpp"

#include <memory>
#include <utility>

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

    Model::Model()
    {
        this->MakeSquare();
    }
    /* Create model with combined data array (vertices, texcoords, and normals) per-vertex */
    Model::Model(std::unique_ptr<GLfloat*>& data, std::unique_ptr<GLint*>& indices, const bool& shouldUseTexcoords, const bool& shouldUseNormals) // Assumes use of heap allocated pointer
    {
        m_data = std::unique_ptr<GLfloat*>(std::move(data));
        m_indices = std::unique_ptr<GLint*>(std::move(indices));
        m_shouldUseTexcoords = shouldUseTexcoords;
        m_shouldUseNormals = shouldUseNormals;
    }

    /* Primitives */
    void Model::MakeSquare()
    {
        m_data = std::make_unique<GLfloat*>(square_vertices_texcoords_normals);
        m_indices = std::make_unique<GLint*>(square_indices);
        m_shouldUseTexcoords = true;
        m_shouldUseNormals = true;
    }

    bool Model::ShouldUseTexcoords() const
    {
        return m_shouldUseTexcoords;
    }
    bool Model::ShouldUseNormals() const
    {
        return m_shouldUseNormals;
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