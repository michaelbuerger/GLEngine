#ifndef GLE_MODEL_HPP
#define GLE_MODEL_HPP

#include "GLEngine/defines.hpp"
#include "GLEngine/graphics/graphics.hpp"
#include "GLEngine/graphics/Texture.hpp"

#include <memory>
#include <utility>

namespace GLEngine
{

class Model
{
public:
    // Model(); // Create model with some primitive and some default texture
    // Model(const GLuint& vao); // Create model with vao and some default texture
    Model(const GLuint &vao, const GLuint &vertexCount, const std::shared_ptr<Texture> &texture);
    Model(const Model &model);

    GLuint GetVAO() const;
    const std::shared_ptr<Texture> &GetTexture() const;
    GLuint GetVertexCount() const;

    void BindVAO() const;
    void UnbindVAO() const;

    void BindTexture() const;
    void UnbindTexture() const;

    /* Bind vao and texture */
    void Bind() const;
    /* Unbind vao and texture */
    void Unbind() const;

private:
    GLuint m_vao;
    std::shared_ptr<Texture> m_texture;
    GLuint m_vertexCount;
};

} // namespace GLEngine

#endif