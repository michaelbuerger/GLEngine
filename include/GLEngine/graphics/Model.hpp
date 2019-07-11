#ifndef MODEL_HPP
#define MODEL_HPP

#include "GLEngine/defines.hpp"
#include "GLEngine/graphics/graphics.hpp"

#include <memory>
#include <utility>

namespace GLEngine { namespace graphics { // KEEP READING UP ON OBJ, NOTE FACES ARE IMPORTANT AND DO EVERYTHING BASED ON INDICES
    
    /* Creates model from default primitive, given data, or previously created model */
    /* Note that this class only works with the use of 3D vertices, UV texcoords (no W), and 3D normals */
    class Model
    {
        public:
            /* Creates model with square primitive data */
            Model();
            /* Create model with combined data array (vertices, texcoords, and normals) per-vertex */
            Model(std::unique_ptr<GLfloat*>& data, std::unique_ptr<GLint*>& indices, const bool& shouldUseTexcoords, const bool& shouldUseNormals);
            Model(const Model& model);

            ~Model();

            /* Primitives */
            void MakeSquare();

            bool ShouldUseTexcoords() const;
            bool ShouldUseNormals() const;

            GLuint GetVAO() const;
            GLuint GetVBO() const;

        private:
            std::unique_ptr<GLfloat*> m_data;
            std::unique_ptr<GLint*> m_indices;
            bool m_shouldUseTexcoords;
            bool m_shouldUseNormals;

            GLuint m_vao;
            GLuint m_vbo; // Only uses one VBO with all data inside of it
    };

}}

#endif