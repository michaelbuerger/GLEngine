#ifndef MODEL_HPP
#define MODEL_HPP

#include "GLEngine/defines.hpp"
#include "GLEngine/graphics/graphics.hpp"

namespace GLEngine { namespace graphics {
    
    /* Creates model from default primitive, given data, or previously created model */
    /* Note that this class only works with the use of 3D vertices, UV texcoords (no W), and 3D normals */
    class Model
    {
        public:
            /* Creates model with square primitive data */
            Model();
            Model(const GLfloat* vertices, const GLfloat* texcoords, const GLfloat* normals);
            Model(const Model& model);

            /* Primitives */
            // static Model triangle;
            static Model square;
            // static Model cube;

            GLfloat *GetVertices();
            GLfloat *GetTexcoords();
            GLfloat *GetNormals();

        private:
            GLfloat m_vertices[];
            GLfloat m_texcoords[];
            GLfloat m_normals[];

            GLuint m_vao;
            GLuint m_vbo; // Only uses one VBO with all data inside of it

            /* Returns new array with per-vertex data in this order: vertex, texcoord, normal */
            GLfloat *GetCombinedData();
    };

}}

#endif