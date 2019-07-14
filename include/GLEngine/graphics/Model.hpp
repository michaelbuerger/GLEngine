#ifndef MODEL_HPP
#define MODEL_HPP

#include "GLEngine/defines.hpp"
#include "GLEngine/graphics/graphics.hpp"
#include "GLEngine/graphics/Texture.hpp"

#include <memory>
#include <utility>

namespace GLEngine { namespace graphics {
    
    class Model
    {
        public:
            // Model(); // Create model with some primitive and some default texture
            // Model(const GLuint& vao); // Create model with vao and some default texture
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