#ifndef MODEL_HPP
#define MODEL_HPP

#include "GLEngine/defines.hpp"
#include "GLEngine/graphics/graphics.hpp"
#include "GLEngine/graphics/Texture.hpp"

#include <memory>
#include <utility>

namespace GLEngine { namespace graphics { // KEEP READING UP ON OBJ, NOTE FACES ARE IMPORTANT AND DO EVERYTHING BASED ON INDICES
    
    /* Creates model from default primitive, given data, or previously created model */
    /* Note that this class only works with the use of 3D vertices, UV texcoords (no W), and 3D normals */
    class Model
    {
        public:
            Model(const GLuint& vao);
            Model(const GLuint& vao, const std::shared_ptr<Texture>& texture);
            Model(const Model& model);

            GLuint GetVAO() const;
            const std::shared_ptr<Texture>& GetTexture() const;

            /* Bind vao and texture */
            void Bind() const;
            /* Unbind vao and texture */
            void Unbind() const;

        private:
            GLuint m_vao;
            std::shared_ptr<Texture> m_texture;
    };

}}

#endif