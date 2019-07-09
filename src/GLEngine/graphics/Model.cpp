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
    }; // KEEP READING UP ON OBJ, NOTE FACES ARE IMPORTANT AND DO EVERYTHING BASED ON INDICES

    Model();
            Model(const GLfloat* vertices, const GLfloat* texcoords, const GLfloat* normals);
            Model(const Model& model);

            /* Primitives */
            // static Model triangle;
            Model square = 
            // static Model cube;

            GLfloat *GetVertices();
            GLfloat *GetTexcoords();
            GLfloat *GetNormals();

            /* Returns new array with per-vertex data in this order: vertex, texcoord, normal */
            GLfloat *GetCombinedData();

}}