#ifndef GLE_MODEL_HPP
#define GLE_MODEL_HPP

#include "GLEngine/defines.hpp"
#include "GLEngine/graphics/graphics.hpp"

#include <memory>
#include <utility>

namespace GLEngine
{

class Model
{
public:
    // Model(); // Create model with some primitive
    // Model(const GLuint& vao); // Create model with vao
    Model(const GLuint &vao, const GLuint &vertexCount);
    Model(const Model &model);

    GLuint GetVAO() const;
    GLuint GetVertexCount() const;

    void Bind() const;
    void Unbind() const;

private:
    GLuint m_vao;
    GLuint m_vertexCount;
};

} // namespace GLEngine

#endif